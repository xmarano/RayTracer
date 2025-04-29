/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.cpp
*/
#include "../include/Plane.hpp"
#include <cmath>

RayTracer::Plane::Plane(const Math::Point3D &point, const Math::Vector3D &normal, std::shared_ptr<IMaterial> material)
    : _point(point), _normal(normal), _material(std::move(material))
{}

void RayTracer::Plane::translate(const Math::Vector3D &v)
{
    _point = _point + v;
}

void RayTracer::Plane::rotate(const Math::Vector3D &axis, double angleDegrees)
{
    _normal = Math::rotateVector(_normal, axis, angleDegrees);
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Plane::getMaterial() const
{
    return _material;
}

bool RayTracer::Plane::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const {
    double denom = _normal.dot(ray.direction);

    if (std::abs(denom) < 1e-6)
        return false;

    t = (_point - ray.origin).dot(_normal) / denom;

    if (t < 0)
        return false;

    hitPoint = ray.origin + ray.direction * t;
    normal = _normal;
    return true;
}
