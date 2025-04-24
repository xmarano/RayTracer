/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.cpp
*/

#include "../include/Sphere.hpp"
#include <cmath>

RayTracer::Sphere::Sphere(const Math::Point3D &center, double radius, std::shared_ptr<IMaterial> material)
    : _center(center),
      _radius(radius),
      _material(std::move(material))
{}

bool RayTracer::Sphere::hits(const Ray &ray) const {
    Math::Vector3D oc = ray.origin - _center;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double delta = b * b - 4 * a * c;
    if (delta < 0.0) return false;
    double sq = std::sqrt(delta);
    double t1 = (-b - sq) / (2 * a);
    double t2 = (-b + sq) / (2 * a);
    return (t1 >= 0.0) || (t2 >= 0.0);
}

void RayTracer::Sphere::translate(const Math::Vector3D &v) {
    _center = _center + v;
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Sphere::getMaterial() const {
    return _material;
}
