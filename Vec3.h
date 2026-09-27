#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vector3
{
    friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);
    friend Vector3 operator+(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator-(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator*(const Vector3 &u, const Vector3 &v);
    friend Vector3 operator*(double t, const Vector3 &v);

    friend double Dot(const Vector3 &u, const Vector3 &v);
    friend Vector3 Cross(const Vector3 &u, const Vector3 &v);

public:
    Vector3() : mElements{0, 0, 0} {}
    Vector3(double e0, double e1, double e2) : mElements{e0, e1, e2} {}

    double X() const { return mElements[0]; }
    double Y() const { return mElements[1]; }
    double Z() const { return mElements[2]; }

    Vector3 operator-() const { return Vector3(-mElements[0], -mElements[1], -mElements[2]); }
    double operator[](int i) const { return mElements[i]; }
    double &operator[](int i) { return mElements[i]; }

    Vector3 &operator+=(const Vector3 &v)
    {
        mElements[0] += v.mElements[0];
        mElements[1] += v.mElements[1];
        mElements[2] += v.mElements[2];
        return *this;
    }

    Vector3 &operator*=(double t)
    {
        mElements[0] *= t;
        mElements[1] *= t;
        mElements[2] *= t;
        return *this;
    }

    Vector3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double Length() const
    {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return mElements[0] * mElements[0] + mElements[1] * mElements[1] + mElements[2] * mElements[2];
    }

    static Vector3 Random()
    {
        return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    static Vector3 Random(double min, double max)
    {
        return Vector3(
            RandomDouble(min, max),
            RandomDouble(min, max),
            RandomDouble(min, max));
    }

private:
    double mElements[3] = {};
};
typedef Vector3 Vec3;

// 기하학적 명시를 위해 사용합니다.
using Point3 = Vector3;

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v.mElements[0] << ' ' << v.mElements[1] << ' ' << v.mElements[2];
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.mElements[0] + v.mElements[0], u.mElements[1] + v.mElements[1], u.mElements[2] + v.mElements[2]);
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.mElements[0] - v.mElements[0], u.mElements[1] - v.mElements[1], u.mElements[2] - v.mElements[2]);
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.mElements[0] * v.mElements[0], u.mElements[1] * v.mElements[1], u.mElements[2] * v.mElements[2]);
}

inline Vector3 operator*(double t, const Vector3 &v)
{
    return Vector3(t * v.mElements[0], t * v.mElements[1], t * v.mElements[2]);
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return t * v;
}

inline Vector3 operator/(const Vector3 &v, double t)
{
    return (1 / t) * v;
}

inline double Dot(const Vector3 &u, const Vector3 &v)
{
    return u.mElements[0] * v.mElements[0] + u.mElements[1] * v.mElements[1] + u.mElements[2] * v.mElements[2];
}

inline Vector3 Cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.mElements[1] * v.mElements[2] - u.mElements[2] * v.mElements[1], u.mElements[2] * v.mElements[0] - u.mElements[0] * v.mElements[2], u.mElements[0] * v.mElements[1] - u.mElements[1] * v.mElements[0]);
}

inline Vector3 UnitVector(const Vector3 &v)
{
    return v / v.Length();
}

#endif