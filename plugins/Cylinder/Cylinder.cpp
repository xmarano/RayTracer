/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"
#include <cmath>
#include "../../include/IMaterial.hpp"

RayTracer::Cylinder::Cylinder()
    : _baseCenter(Math::Point3D(0, 0, 0)),
      _radius(1.0),
      _height(1.0),
      _axis(Math::Vector3D(0, 1, 0)),
      _center(Math::Point3D(0, 0, 0)),
      _material(nullptr)
{}

RayTracer::Cylinder::Cylinder(const Math::Point3D &baseCenter, double radius, double height, std::shared_ptr<RayTracer::IMaterial> material)
    : _baseCenter(baseCenter),
      _radius(radius),
      _height(height),
      _axis(Math::Vector3D(0, 1, 0)),
      _center(baseCenter),
      _material(std::move(material))
{}

void RayTracer::Cylinder::translate(const Math::Vector3D &v) {
    _baseCenter = _baseCenter + v;
}

void RayTracer::Cylinder::rotate(const Math::Vector3D &axis, double angleDegrees) {
    _axis = Math::rotateVector(_axis, axis, angleDegrees);
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Cylinder::getMaterial() const {
    return _material;
}

bool RayTracer::Cylinder::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const {
    Math::Vector3D oc = ray.origin - _center;

    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2.0 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
    double c = oc.x * oc.x + oc.z * oc.z - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double sqrtDisc = std::sqrt(discriminant);
    double t0 = (-b - sqrtDisc) / (2 * a);
    double t1 = (-b + sqrtDisc) / (2 * a);

    if (t0 > t1)
        std::swap(t0, t1);

    double y0 = oc.y + t0 * ray.direction.y;
    double y1 = oc.y + t1 * ray.direction.y;

    if (y0 < 0 || y0 > _height) {
        if (y1 < 0 || y1 > _height)
            return false;
        t = t1;
    } else {
        t = t0;
    }

    hitPoint = ray.origin + ray.direction * t;

    Math::Vector3D temp(hitPoint.x - _center.x, 0.0, hitPoint.z - _center.z);
    double length = std::sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
    normal = (length != 0) ? temp / length : temp;

    return true;
}

void RayTracer::Cylinder::setPosition(const Math::Point3D &pos) {
    _center = pos;
    _baseCenter = pos;
}

void RayTracer::Cylinder::setRadius(double r) {
    _radius = r;
}

void RayTracer::Cylinder::setMaterial(std::shared_ptr<IMaterial> material) {
    _material = std::move(material);
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create() {
    return std::make_unique<RayTracer::Cylinder>();
}
