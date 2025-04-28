/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Math3D.cpp
*/
#include "../include/Math3D.hpp"
#include <cmath>

Math::Vector3D::Vector3D() : x(0), y(0), z(0)
{}

Math::Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

double Math::Vector3D::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double Math::Vector3D::dot(const Vector3D &o) const
{
    return x * o.x + y * o.y + z * o.z;
}

Math::Vector3D Math::Vector3D::operator+(const Vector3D &o) const
{
    return Vector3D(x + o.x, y + o.y, z + o.z);
}

Math::Vector3D Math::Vector3D::operator-(const Vector3D &o) const
{
    return Vector3D(x - o.x, y - o.y, z - o.z);
}

Math::Vector3D Math::Vector3D::operator*(double s) const
{
    return Vector3D(x * s, y * s, z * s);
}

Math::Vector3D Math::Vector3D::operator/(double s) const
{
    return Vector3D(x / s, y / s, z / s);
}

Math::Vector3D& Math::Vector3D::operator+=(const Vector3D &o)
{
    x += o.x; y += o.y; z += o.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator-=(const Vector3D &o)
{
    x -= o.x; y -= o.y; z -= o.z;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator*=(double s)
{
    x *= s; y *= s; z *= s;
    return *this;
}

Math::Vector3D& Math::Vector3D::operator/=(double s)
{
    x /= s; y /= s; z /= s;
    return *this;
}


Math::Point3D::Point3D() : x(0), y(0), z(0)
{}

Math::Point3D::Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Math::Point3D Math::Point3D::operator+(const Vector3D &v) const
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Math::Point3D Math::Point3D::operator-(const Vector3D &v) const
{
    return Point3D(x - v.x, y - v.y, z - v.z);
}

Math::Vector3D Math::Point3D::operator-(const Point3D &p) const
{
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Math::Vector3D Math::rotateVector(const Math::Vector3D &v, const Math::Vector3D &axis, double angleDegrees)
{
    double rad = angleDegrees * M_PI / 180.0;
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);

    Math::Vector3D normalizedAxis = axis;
    double len = normalizedAxis.length();
    if (len != 0)
        normalizedAxis = normalizedAxis / len;

    double ux = normalizedAxis.x;
    double uy = normalizedAxis.y;
    double uz = normalizedAxis.z;

    Math::Vector3D rotated;
    rotated.x = (cosA + (1 - cosA) * ux * ux) * v.x
              + ((1 - cosA) * ux * uy - sinA * uz) * v.y
              + ((1 - cosA) * ux * uz + sinA * uy) * v.z;

    rotated.y = ((1 - cosA) * uy * ux + sinA * uz) * v.x
              + (cosA + (1 - cosA) * uy * uy) * v.y
              + ((1 - cosA) * uy * uz - sinA * ux) * v.z;

    rotated.z = ((1 - cosA) * uz * ux - sinA * uy) * v.x
              + ((1 - cosA) * uz * uy + sinA * ux) * v.y
              + (cosA + (1 - cosA) * uz * uz) * v.z;

    return rotated;
}
