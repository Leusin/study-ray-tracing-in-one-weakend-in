#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord
{
public:
    void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
    {
        bFrontFace = Dot(ray.Direction(), outwardNormal) < 0;
        normal = bFrontFace ? outwardNormal : -outwardNormal;
    }

    Point point;
    Vec3 normal;
    double t;
    bool bFrontFace;
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &rec) const = 0;
};

#endif