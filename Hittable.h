#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Interval.h"

class HitRecord
{
public:
    void SetFaceNormal(const Ray &ray, const Vec3 &outwardNormal)
    {
        bFrontFace = Dot(ray.Direction(), outwardNormal) < 0;
        Normal = bFrontFace ? outwardNormal : -outwardNormal;
    }

    Point3 Point;
    Vec3 Normal;
    double T;
    bool bFrontFace;
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(
        const Ray &ray,
        const Interval &rayT,
        HitRecord &rec) const = 0;
};

#endif