#include "RTWeekend.h"

#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include <iostream>

Color RayColor(const Ray &ray, const Hittable& world)
{
    HitRecord hitRecord;
    if (world.Hit(ray, Interval(0.0, Infinity), hitRecord))
    {
        return 0.5 * (hitRecord.Normal + Color(1.0, 1.0, 1.0));
    }

    Vector3 unitDirection = UnitVector(ray.Direction());
    auto a = 0.5 * (unitDirection.Y() + 1.0); // 0.0 ~ 1.0
    
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

    Camera camera;
    camera.AspectRatio = 16.0 / 9.0;
    camera.ImageWidth = 400;

    camera.Render(world);

    return 0;
}