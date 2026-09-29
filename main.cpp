#include "RTWeekend.h"

#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Lambertian.h"
#include "Dielectric.h"
#include "Metal.h"
#include "Sphere.h"

#include <iostream>

Color RayColor(const Ray &ray, const Hittable &world)
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

    // {
    //     auto r = std::cos(Pi / 4);
    //     auto materalLeft = std::make_shared<Lambertian>(Color(0.0, 0.0, 1.0));
    //     auto materalRight = std::make_shared<Lambertian>(Color(1.0, 0.0, 0.0));
    //     world.Add(std::make_shared<Sphere>(Point3(-r, 0.0, -1.0), r, materalLeft));
    //     world.Add(std::make_shared<Sphere>(Point3(r, 0.0, -1.0), r, materalRight));
    // }

    // {
    //     auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    //     auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    //     auto materalLeft = std::make_shared<Dielectric>(1.50);
    //     auto materalBubble = std::make_shared<Dielectric>(1.00 / 1.50);
    //     auto materalRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    //     world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    //     world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    //     world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materalLeft));
    //     world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materalBubble));
    //     world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materalRight));
    // }

    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, groundMaterial));

    for (int gridX = -11; gridX < 11; gridX++)
    {
        for (int gridZ = -11; gridZ < 11; gridZ++)
        {
            const double materialSelector = RandomDouble();

            const Point3 center(gridX + 0.9 * RandomDouble(),
                                0.2,
                                gridZ + 0.9 * RandomDouble());

            if ((center - Point3(4.0, 0.2, 0.0)).Length() > 0.9)
            {
                std::shared_ptr<Material> sphereMaterial;

                if (materialSelector < 0.8)
                {
                    const Color albedo = Color::Random() * Color::Random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                }
                else if (materialSelector < 0.95)
                {
                    const Color albedo = Color::Random(0.5, 1.0);
                    const double fuzz = RandomDouble(0.0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                }
                else
                {
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                }

                world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, material3));

    Camera camera;

    camera.AspectRatio = 16.0 / 9.0;
    camera.ImageWidth = 1200;
    camera.SamplesPerPixel = 500;
    camera.MaxDepth = 50;
    
    camera.VFov = 20.0;
    camera.Lookfrom = Point3(13.0, 2.0, 3.0);
    camera.Lookat = Point3(0.0, 0.0, 0.0);
    camera.VUp = Vec3(0.0, 1.0, 0.0);

    camera.DefocusAngle = 0.6;
    camera.FocusDist = 10.0;

    camera.Render(world);

    return 0;
}