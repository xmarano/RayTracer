/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cone.cpp
*/

#include "../include/Cone.hpp"
#include <cmath>

RayTracer::Cone::Cone(const Math::Point3D &apex,
                      double height,
                      double radius,
                      std::shared_ptr<RayTracer::IMaterial> material)
    : _apex(apex), _height(height), _radius(radius), _material(std::move(material)) {}


bool RayTracer::Cone::hits(const RayTracer::Ray &ray) const {

    Math::Vector3D d = ray.direction;
    Math::Vector3D oc = ray.origin - _apex;

    double k = _radius / _height;
    double k2 = k * k;

    double dx = d.x;
    double dy = d.y;
    double dz = d.z;

    double ox = oc.x;
    double oy = oc.y;
    double oz = oc.z;

    double a = dx * dx + dy * dy - k2 * dz * dz;
    double b = 2 * (dx * ox + dy * oy - k2 * dz * oz);
    double c = ox * ox + oy * oy - k2 * oz * oz;

    double delta = b * b - 4 * a * c;
    if (delta < 0.0)
        return false;

    double sqrtd = std::sqrt(delta);
    double t1 = (-b - sqrtd) / (2 * a);
    double t2 = (-b + sqrtd) / (2 * a);

    double z1 = ray.origin.z + t1 * d.z;
    double z2 = ray.origin.z + t2 * d.z;
    double baseZ = _apex.z - _height;

    return (t1 >= 0.0 && z1 <= _apex.z && z1 >= baseZ) ||
           (t2 >= 0.0 && z2 <= _apex.z && z2 >= baseZ);
}

void RayTracer::Cone::translate(const Math::Vector3D &v) {
    _apex = _apex + v;
}

void RayTracer::Cone::rotate(const Math::Vector3D &axis, double angleDegrees)
{
    _axis = Math::rotateVector(_axis, axis, angleDegrees);
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Cone::getMaterial() const {
    return _material;
}