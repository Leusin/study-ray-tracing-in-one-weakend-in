#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "Interval.h"

#include <iostream>

using Color = Vec3;

inline double LinearToGamma(double linearComponent)
{
    if(linearComponent > 0.0)
    {
        return std::sqrt(linearComponent);
    }

    return 0.0;
}

void WriteColor(std::ostream &out, const Color &pixelColor)
{
    auto red = pixelColor.X();
    auto green = pixelColor.Y();
    auto blue = pixelColor.Z();

    red = LinearToGamma(red);
    green = LinearToGamma(green);
    blue = LinearToGamma(blue);

    static const Interval intensity(0.000, 0.999);

    int redByte = static_cast<int>(256.0 * intensity.Clamp(red));
    int greenByte = static_cast<int>(256.0 * intensity.Clamp(green));
    int blueByte = static_cast<int>(256.0 * intensity.Clamp(blue));

    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}

#endif