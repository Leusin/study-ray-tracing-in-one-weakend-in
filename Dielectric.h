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

        const double etaInOverEtaOut = hitRecord.IsFrontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

        const Vec3 unitDirection = UnitVector(rayIn.Direction());
        const Vec3 refacted = Refract(unitDirection, hitRecord.Normal, etaInOverEtaOut);

        scattered = Ray(hitRecord.Point, refacted);

        return true;
    }

private:
    double mRefractionIndex = 1.0;
};