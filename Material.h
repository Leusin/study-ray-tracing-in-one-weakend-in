#pragma once

#include "Hittable.h"

class Material
{
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray &rayIn, const HitRecord &HitRecord, Color &attenuation, Ray &scattered) const
    {
        return false;
    }
};