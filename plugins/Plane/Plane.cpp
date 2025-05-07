/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.cpp
*/
#include "Plane.hpp"
#include <cmath>
#include "../../include/IMaterial.hpp"

RayTracer::Plane::Plane() {}

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

bool RayTracer::Plane::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const
{
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

void RayTracer::Plane::setPosition(const Math::Point3D &pos)
{
    _point = pos;
}

void RayTracer::Plane::setRadius(double)
{
}

void RayTracer::Plane::setMaterial(std::shared_ptr<IMaterial> material)
{
    _material = std::move(material);
}

void RayTracer::Plane::setAxis(char axis)
{
    if (axis == 'X') _normal = Math::Vector3D(1, 0, 0);
    else if (axis == 'Y') _normal = Math::Vector3D(0, 1, 0);
    else if (axis == 'Z') _normal = Math::Vector3D(0, 0, 1);
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create()
{
    return std::make_unique<RayTracer::Plane>();
}

