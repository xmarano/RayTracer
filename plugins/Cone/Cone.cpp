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
    Math::Vector3D A = _axis;
    double lenA = A.length();
    if (lenA == 0) return false;
    A = A / lenA;

    Math::Vector3D V = ray.origin - _apex;

    double dA = ray.direction.dot(A);
    Math::Vector3D Dp = ray.direction - A * dA;

    double vA = V.dot(A);
    Math::Vector3D Vp = V - A * vA;

    double k = _radius / _height;
    k = k * k;

    double a = Dp.dot(Dp) - k * dA * dA;
    double b = 2 * (Dp.dot(Vp) - k * dA * vA);
    double c = Vp.dot(Vp) - k * vA * vA;

    double disc = b * b - 4 * a * c;
    if (disc < 0) return false;

    double sq = std::sqrt(disc);
    double t0 = (-b - sq) / (2 * a);
    double t1 = (-b + sq) / (2 * a);
    if (t0 > t1) std::swap(t0, t1);

    double y0 = vA + t0 * dA;
    double y1 = vA + t1 * dA;
    if (y0 < 0 || y0 > _height) {
        if (y1 < 0 || y1 > _height) return false;
        t = t1;
    } else {
        t = t0;
    }

    hitPoint = ray.origin + ray.direction * t;

    Math::Point3D axisPoint = _apex + A * (vA + t * dA);
    Math::Vector3D N = hitPoint - axisPoint;
    normal = N / N.length();

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

void RayTracer::Cone::setHeight(double height)
{
    _height = height;
}

void RayTracer::Cone::setCoAxis(const Math::Vector3D &axis)
{
    double len = axis.length();
    _axis = (len > 0) ? axis / len : Math::Vector3D{0,1,0};
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create()
{
    return std::make_unique<RayTracer::Cone>();
}