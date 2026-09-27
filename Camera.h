#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable.h"
#include "Material.h"

class Camera
{
public:
    double AspectRatio = 1.0;
    int ImageWidth = 100;
    int SamplesPerPixel = 10;
    int MaxDepth = 10;

    void Render(const Hittable &world)
    {
        Initialize();

        std::cout << "P3\n"
                  << ImageWidth << ' ' << mImageHeight << "\n255\n";

        for (int scanlineIndex = 0; scanlineIndex < mImageHeight; scanlineIndex++)
        {
            std::clog
                << "\rScanlines remaining: "
                << (mImageHeight - scanlineIndex)
                << ' '
                << std::flush;

            for (int pixelIndex = 0; pixelIndex < ImageWidth; pixelIndex++)
            {
                Color pixelColor(0.0, 0.0, 0.0);

                for (int sampleIndex = 0; sampleIndex < SamplesPerPixel; sampleIndex++)
                {
                    auto ray = GetRay(pixelIndex, scanlineIndex);
                    pixelColor += RayColor(ray, MaxDepth, world);
                }

                WriteColor(std::cout, mPixelSamplesScale * pixelColor);
            }
        }

        std::clog << "\rDone.                \n";
    }

private:
    void Initialize()
    {
        mImageHeight = static_cast<int>(ImageWidth / AspectRatio);
        mImageHeight = (mImageHeight < 1) ? 1 : mImageHeight;

        mPixelSamplesScale = 1.0 / static_cast<double>(SamplesPerPixel);

        mCenter = Point3(0.0, 0.0, 0.0);

        auto focalLength = 1.0;
        auto viewportHeight = 2.0;
        auto viewportWidth = viewportHeight * (static_cast<double>(ImageWidth) / static_cast<double>(mImageHeight));

        auto viewportU = Vec3(viewportWidth, 0.0, 0.0);
        auto viewportV = Vec3(0.0, -viewportHeight, 0.0);

        mPixelDeltaU = viewportU / ImageWidth;
        mPixelDeltaV = viewportV / mImageHeight;

        auto viewportUpperLeft =
            mCenter - Vec3(0.0, 0.0, focalLength) - viewportU / 2.0 - viewportV / 2.0;

        mPixel00Location = viewportUpperLeft + 0.5 * (mPixelDeltaU + mPixelDeltaV);
    }

    Ray GetRay(int pixelIndex, int scanlineIndex) const
    {
        auto offset = SampleSquare();

        auto pixelSample =
            mPixel00Location + ((pixelIndex + offset.X()) * mPixelDeltaU) + ((scanlineIndex + offset.Y()) * mPixelDeltaV);

        auto rayOrigin = mCenter;
        auto rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    Vec3 SampleSquare() const
    {
        return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0.0);
    }

    Color RayColor(const Ray &ray, int depth, const Hittable &world) const
    {
        if (depth <= 0)
        {
            return Color(0.0, 0.0, 0.0);
        }

        HitRecord hitRecord;

        if (world.Hit(ray, Interval(0.001, Infinity), hitRecord))
        {
            Ray scattered;
            Color attenuation;

            if (hitRecord.Mat->Scatter(ray, hitRecord, attenuation, scattered))
            {
                return attenuation * RayColor(scattered, depth - 1, world);;
            }
            return Color(0.0, 0.0, 0.0);
        }

        Vec3 unitDirection = UnitVector(ray.Direction());
        auto a = 0.5 * (unitDirection.Y() + 1.0);

        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

private:
    int mImageHeight = 0;
    double mPixelSamplesScale = 1.0;

    Point3 mCenter;
    Point3 mPixel00Location;
    Vec3 mPixelDeltaU;
    Vec3 mPixelDeltaV;
};

#endif