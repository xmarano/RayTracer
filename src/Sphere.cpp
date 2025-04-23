/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.cpp
*/

#include "../include/Sphere.hpp"
#include <cmath>

using namespace RayTracer;

Sphere::Sphere(Math::Point3D _center, double _radius, Color _color)
    : center(_center), radius(_radius), color(_color) {}

bool Sphere::hits(const Ray &ray) const {
    Math::Vector3D oc = ray.origin - center;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;

    double delta = b*b - 4*a*c;
    if (delta < 0.0)
        return false;

    double sqrtd = std::sqrt(delta);
    double s1 = (-b - sqrtd) / (2.0 * a);
    double s2 = (-b + sqrtd) / (2.0 * a);
    return s1 >= 0.0 || s2 >= 0.0;
}

void Sphere::translate(const Math::Vector3D &v) {
    center = center + v;
}

const Color &Sphere::getColor() const {
    return color;
}
