/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.cpp
*/
#include "Cylinder.hpp"
#include <cmath>
#include "../../include/IMaterial.hpp"

RayTracer::Cylinder::Cylinder() : _baseCenter{0,0,0}, _radius(1.0), _height(1.0), _axis{0,1,0}, _material(nullptr)
{
    _axis /= _axis.length();
}

void RayTracer::Cylinder::translate(const Math::Vector3D &v)
{
    _baseCenter = _baseCenter + v;
}

void RayTracer::Cylinder::rotate(const Math::Vector3D &axis, double angleDegrees)
{
    _axis = Math::rotateVector(_axis, axis, angleDegrees);
    _axis /= _axis.length();
}

std::shared_ptr<RayTracer::IMaterial> RayTracer::Cylinder::getMaterial() const
{
    return _material;
}

bool RayTracer::Cylinder::intersect(const RayTracer::Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const
{
    Math::Vector3D A = _axis / _axis.length();
    Math::Vector3D OC = ray.origin - _baseCenter;

    double dA = ray.direction.dot(A);
    Math::Vector3D Dp = ray.direction - A * dA;

    double oA = OC.dot(A);
    Math::Vector3D Op = OC - A * oA;

    double a = Dp.dot(Dp);
    double b = 2.0 * Dp.dot(Op);
    double c = Op.dot(Op) - _radius * _radius;
    double disc = b * b - 4 * a * c;
    if (disc < 0.0) return false;

    double sq  = std::sqrt(disc);
    double t0  = (-b - sq) / (2.0 * a);
    double t1  = (-b + sq) / (2.0 * a);
    if (t0 > t1) std::swap(t0, t1);

    double y0 = oA + t0 * dA;
    double y1 = oA + t1 * dA;

    if (y0 < 0.0 || y0 > _height) {
        if (y1 < 0.0 || y1 > _height) return false;
        t = t1;
    } else {
        t = t0;
    }

    hitPoint = ray.origin + ray.direction * t;
    Math::Point3D axisHit = _baseCenter + A * (oA + t * dA);
    Math::Vector3D N = hitPoint - axisHit;
    normal = N / N.length();
    return true;
}

void RayTracer::Cylinder::setPosition(const Math::Point3D &pos)
{
    _baseCenter = pos;
}

void RayTracer::Cylinder::setRadius(double r)
{
    _radius = r;
}

void RayTracer::Cylinder::setHeight(double height)
{
    _height = height;
}

void RayTracer::Cylinder::setCoAxis(const Math::Vector3D &axis)
{
    double len = axis.length();
    _axis = (len > 0.0) ? axis / len : Math::Vector3D{0,1,0};
}

void RayTracer::Cylinder::setMaterial(std::shared_ptr<RayTracer::IMaterial> material)
{
    _material = std::move(material);
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create()
{
    return std::make_unique<RayTracer::Cylinder>();
}
