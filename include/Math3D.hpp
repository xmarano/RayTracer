/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Math3D.hpp
*/

#pragma once
#include <cmath>
#include <iostream>

namespace Math {

    class Vector3D {
    public:
        double x, y, z;

        Vector3D();
        Vector3D(double x_, double y_, double z_);

        double length() const;
        double dot(const Vector3D &o) const;

        Vector3D operator+(const Vector3D &o) const;
        Vector3D operator-(const Vector3D &o) const;
        Vector3D operator*(double s) const;
        Vector3D operator/(double s) const;

        Vector3D& operator+=(const Vector3D &o);
        Vector3D& operator-=(const Vector3D &o);
        Vector3D& operator*=(double s);
        Vector3D& operator/=(double s);
    };

    class Point3D {
    public:
        double x, y, z;

        Point3D();
        Point3D(double x_, double y_, double z_);

        Point3D operator+(const Vector3D &v) const;
        Point3D operator-(const Vector3D &v) const;
        Vector3D operator-(const Point3D &p) const;
    };

}
