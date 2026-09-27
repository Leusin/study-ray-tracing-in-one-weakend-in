#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
    explicit Lambertian(const Color &albedo)
        : mAlbedo(albedo)
    {
    }

    bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Color &attenuation, Ray &scattered) const override
    {
        auto scatterDirection = hitRecord.Normal + RandomUnitVector();

        if (scatterDirection.NearZero())
        {
            scatterDirection = hitRecord.Normal;
        }

        scattered = Ray(hitRecord.Point, scatterDirection);
        attenuation = mAlbedo;

        return true;
    }

private:
    Color mAlbedo;
};