#include "material.h"

class Dielectric : public Material
{
public:
    explicit Dielectric(double refractionIndex)
        : mRefractionIndex(refractionIndex)
    {
    }

    bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Color &attenuation, Ray &scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);

        const double refractionRatio = hitRecord.IsFrontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

        const Vec3 unitDirection = UnitVector(rayIn.Direction());

        const double cosTheta = std::fmin(Dot(-unitDirection, hitRecord.Normal), 1.0);

        const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

        const bool cannotRefract = refractionRatio * sinTheta > 1.0;

        Vec3 direction;

        if (cannotRefract)
        {
            direction = Reflect(unitDirection, hitRecord.Normal);
        }
        else
        {
            direction = Refract (unitDirection, hitRecord.Normal, refractionRatio);
        }

        scattered = Ray(hitRecord.Point, direction);

        return true;
    }

private:
    double mRefractionIndex = 1.0;
};