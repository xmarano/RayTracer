/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cone.cpp
*/
#include "Cone.hpp"
#include <cmath>
#include "../../include/IMaterial.hpp"

RayTracer::Cone::Cone() : _apex(Math::Point3D(0, 0, 0)), _height(1.0), _radius(1.0), _axis(Math::Vector3D(0, 1, 0)), _material(nullptr)
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
    normal = (length != 0) ? tmp / length : tmp;

    return true;
}


void RayTracer::Cone::setPosition(const Math::Point3D &pos)
{
    _apex = pos;
}

void RayTracer::Cone::setRadius(double r)
{
    _radius = r;
}

void RayTracer::Cone::setMaterial(std::shared_ptr<IMaterial> material)
{
    _material = std::move(material);
}

void RayTracer::Cone::setCoAxis(const Math::Vector3D &axis)
{
    _axis = axis;
}

void RayTracer::Cone::setHeight(double height)
{
    _height = height;
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create()
{
    return std::make_unique<RayTracer::Cone>();
}
