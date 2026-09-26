#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

#include <iostream>

Color RayColor(const Ray& r)
{
    Vector3 unitDirection = UnitVector(r.Direction());
    auto a = 0.5 * (unitDirection.Y() + 1); // 0.0 ~ 1.0
    
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0, 0, 0);

    auto viewportU = Vec3(viewportWidth, 0, 0);
    auto viewportV = Vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft = cameraCenter 
        - Vec3(0, 0, focalLength) 
        - viewportU / 2 
        - viewportV / 2;
    auto pixel00Loc = viewportUpperLeft 
        + 0.5 * (pixelDeltaU + pixelDeltaV); 

    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\nScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i =0;i <imageWidth; i++)
        {
            auto pixelCenter = pixel00Loc 
                + (i * pixelDeltaU) 
                + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            Color pixelColor = RayColor(r);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                \n";
    return 0;
}