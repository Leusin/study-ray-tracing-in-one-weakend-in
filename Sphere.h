#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3 &center, double radius)
        : mCenter(center), mRadius(std::fmax(0.0, radius))
    {
    }

    bool Hit(
        const Ray& ray,
        const Interval& rayT,
        HitRecord& hitRecord
    ) const override
    {
        Vec3 originToCenter = mCenter - ray.Origin();

        auto a = ray.Direction().LengthSquared();
        auto h = Dot(ray.Direction(), originToCenter);
        auto c = originToCenter.LengthSquared() - mRadius * mRadius;

        auto discriminant = h * h - a * c;
        if(discriminant < 0.0)
        {
            return false;
        }

        auto squareRootDiscriminant = std::sqrt(discriminant);

        auto root = (h - squareRootDiscriminant) / a;
        if (!rayT.Contains(root))
        {
            root = (h + squareRootDiscriminant) / a;
            if(!rayT.Contains(root))
            {
                return false;
            }
        }

        hitRecord.T = root;
        hitRecord.Point = ray.At(hitRecord.T);
        
        auto outwardNormal = (hitRecord.Point - mCenter) / mRadius;
        hitRecord.SetFaceNormal(ray, outwardNormal);

        return true;
    }

private:
    Point3 mCenter;
    double mRadius;
};

#endif