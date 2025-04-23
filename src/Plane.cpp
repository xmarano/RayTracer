/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.cpp
*/


#include "../include/Plane.hpp"
#include <cmath>

using namespace RayTracer;

Plane::Plane(Math::Point3D _point, Math::Vector3D _normal, Color _color)
    : point(_point), normal(_normal), color(_color) {}

bool Plane::hits(const Ray &ray) const {
    double denom = normal.dot(ray.direction);
    if (std::abs(denom) < 1e-6)
        return false;

    double t = (point - ray.origin).dot(normal) / denom;
    return t >= 0;
}

void Plane::translate(const Math::Vector3D &v) {
    point = point + v;
}

const Color &Plane::getColor() const {
    return color;
}

