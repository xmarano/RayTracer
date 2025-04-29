/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cone.cpp
*/
#include "../include/Cone.hpp"
#include <cmath>

RayTracer::Cone::Cone(const Math::Point3D &apex, double height, double radius, std::shared_ptr<RayTracer::IMaterial> material)
    : _apex(apex), _height(height), _radius(radius), _material(std::move(material))
{}

void RayTracer::Cone::translate(const Math::Vector3D &v)
{
    _apex = _apex + v;
}

void RayTracer::Cone::rotate(const Math::Vector3D &axis, double angleDegrees)
{
    _axis = Math::rotateVector(_axis, axis, angleDegrees);
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Cone::getMaterial() const
{
    return _material;
}

bool RayTracer::Cone::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const
{
    Math::Vector3D oc = ray.origin - _apex;
    double k = _radius / _height;
    k = k * k;

    double dx = ray.direction.x;
    double dy = ray.direction.y;
    double dz = ray.direction.z;
    double ox = oc.x;
    double oy = oc.y;
    double oz = oc.z;

    double a = dx * dx + dz * dz - k * dy * dy;
    double b = 2 * (ox * dx + oz * dz - k * oy * dy);
    double c = ox * ox + oz * oz - k * oy * oy;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double sqrtDisc = std::sqrt(discriminant);
    double t0 = (-b - sqrtDisc) / (2 * a);
    double t1 = (-b + sqrtDisc) / (2 * a);

    if (t0 > t1)
        std::swap(t0, t1);

    double y = oy + t0 * dy;
    if (y < 0 || y > _height) {
        y = oy + t1 * dy;
        if (y < 0 || y > _height)
            return false;
        t = t1;
    } else {
        t = t0;
    }

    hitPoint = ray.origin + ray.direction * t;

    Math::Vector3D tmp = hitPoint - _apex;
    tmp.y = -(k * std::sqrt(tmp.x * tmp.x + tmp.z * tmp.z));
    double length = std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
    if (length != 0)
        normal = tmp / length;
    else
        normal = tmp;

    return true;
}
