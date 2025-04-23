/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.cpp
*/


#include "../include/Plane.hpp"
#include <cmath>

using namespace RayTracer;

Plane::Plane() : point(), normal(), color() {}

Plane::Plane(const Math::Point3D &p, const Math::Vector3D &n, const Color &c)
    : point(p), normal(n), color(c) {}

bool Plane::hits(const Ray &ray) const
{
    double denom = normal.dot(ray.direction);
    if (std::abs(denom) < 1e-6)
        return false;

    double t = (point - ray.origin).dot(normal) / denom;
    return t >= 0;
}
