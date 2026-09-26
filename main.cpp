#include "RTWeekend.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include "Ray.h"
#include "Color.h"
#include "Vec3.h"

#include <iostream>

double HitSphere(const Point &center, double radius, const Ray &ray)
{
    Vec3 oc = center - ray.Origin();
    auto a = ray.Direction().LengthSquared();
    auto h = Dot(ray.Direction(), oc);
    auto c = oc.LengthSquared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0.0)
    {
        return -1.0;
    }

    return (h - std::sqrt(discriminant)) / a;
}

Color RayColor(const Ray &ray, const Hittable& world)
{
    HitRecord HitRecord;
    if (world.Hit(ray, 0.0, Infinity, HitRecord))
    {
        return 0.5 * (HitRecord.normal + Color(1.0, 1.0, 1.0));
    }

    Vector3 unitDirection = UnitVector(ray.Direction());
    auto a = 0.5 * (unitDirection.Y() + 1.0); // 0.0 ~ 1.0
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

    // camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0, 0, 0);

    auto viewportU = Vec3(viewportWidth, 0, 0);
    auto viewportV = Vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\nScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        
        for (int i = 0; i < imageWidth; i++)
        {
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            Color pixelColor = RayColor(r, world);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                \n";
    return 0;
}