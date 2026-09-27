#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

constexpr double Infinity = std::numeric_limits<double>::infinity();
constexpr double Pi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees)
{
    return degrees * Pi / 180.0;
}

// [0.0, 1.0) 사이의 실수형 난수를 반환 합니다.
inline double RandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// [min, max) 사이의 실수형 난수를 반환합니다.
inline double RandomDouble(double min, double max)
{
    return min + (max - min) * RandomDouble();
}

#include "Color.h"
#include "Interval.h"
#include "Ray.h"
#include "Vec3.h"

#endif