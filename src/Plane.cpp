/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.cpp
*/

#include "../include/Plane.hpp"
#include <cmath>

RayTracer::Plane::Plane(const Math::Point3D &point, const Math::Vector3D &normal, std::shared_ptr<IMaterial> material)
    : _point(point),
      _normal(normal),
      _material(std::move(material))
{}

bool RayTracer::Plane::hits(const Ray &ray) const {
    double denom = _normal.dot(ray.direction);
    if (std::abs(denom) < 1e-6)
        return false;
    double t = (_point - ray.origin).dot(_normal) / denom;
    return t >= 0.0;
}

void RayTracer::Plane::translate(const Math::Vector3D &v) {
    _point = _point + v;
}

void RayTracer::Plane::rotate(const Math::Vector3D &axis, double angleDegrees)
{
    _normal = Math::rotateVector(_normal, axis, angleDegrees);
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Plane::getMaterial() const {
    return _material;
}
