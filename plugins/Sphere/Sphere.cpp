/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.cpp
*/
#include "Sphere.hpp"
#include <cmath>

RayTracer::Sphere::Sphere()
    : _center(Math::Point3D(0, 0, 0)), _radius(0.0), _material(nullptr) {}

void RayTracer::Sphere::setPosition(const Math::Point3D &pos) {
    _center = pos;
}

void RayTracer::Sphere::setRadius(double radius) {
    _radius = radius;
}

void RayTracer::Sphere::setMaterial(std::shared_ptr<IMaterial> material) {
    _material = std::move(material);
}

bool RayTracer::Sphere::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const {
    Math::Vector3D oc = ray.origin - _center;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double sqrtDiscriminant = std::sqrt(discriminant);
    double t0 = (-b - sqrtDiscriminant) / (2.0 * a);
    double t1 = (-b + sqrtDiscriminant) / (2.0 * a);
    t = (t0 > 0) ? t0 : ((t1 > 0) ? t1 : -1);

    if (t < 0)
        return false;

    hitPoint = ray.origin + ray.direction * t;
    normal = (hitPoint - _center) / _radius;
    return true;
}

void RayTracer::Sphere::translate(const Math::Vector3D &v) {
    _center = _center + v;
}

void RayTracer::Sphere::rotate(const Math::Vector3D &, double) {}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Sphere::getMaterial() const {
    return _material;
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create() {
    return std::make_unique<RayTracer::Sphere>();
}
