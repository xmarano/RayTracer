/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.cpp
*/

/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder.cpp
*/

#include "../include/Cylinder.hpp"
#include <cmath>

RayTracer::Cylinder::Cylinder(const Math::Point3D &baseCenter, double radius,
        double height, std::shared_ptr<RayTracer::IMaterial> material)
    : _baseCenter(baseCenter), _radius(radius), _height(height), _material(std::move(material)) {}

bool RayTracer::Cylinder::hits(const RayTracer::Ray &ray) const {

    Math::Vector3D d = ray.direction;
    Math::Vector3D oc = ray.origin - _baseCenter;

    double a = d.x * d.x + d.y * d.y;
    double b = 2 * (oc.x * d.x + oc.y * d.y);
    double c = oc.x * oc.x + oc.y * oc.y - _radius * _radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0.0)
        return false;

    double sqrtd = std::sqrt(delta);
    double t1 = (-b - sqrtd) / (2 * a);
    double t2 = (-b + sqrtd) / (2 * a);

    double z1 = ray.origin.z + t1 * d.z;
    double z2 = ray.origin.z + t2 * d.z;

    return (t1 >= 0.0 && z1 >= _baseCenter.z && z1 <= _baseCenter.z + _height) ||
           (t2 >= 0.0 && z2 >= _baseCenter.z && z2 <= _baseCenter.z + _height);
}

void RayTracer::Cylinder::translate(const Math::Vector3D &v) {
    _baseCenter = _baseCenter + v;
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Cylinder::getMaterial() const {
    return _material;
}

