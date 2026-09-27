#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Interval.h"

class Material;

class HitRecord
{
public:
    void SetFaceNormal(const Ray &ray, const Vec3 &outwardNormal)
    {
        IsFrontFace = Dot(ray.Direction(), outwardNormal) < 0.0;
        Normal = IsFrontFace ? outwardNormal : -outwardNormal;
    }

    Point3 Point;
    Vec3 Normal;
    std::shared_ptr<Material> Mat;
    double T;
    bool IsFrontFace;
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