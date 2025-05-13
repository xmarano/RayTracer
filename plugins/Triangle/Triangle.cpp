/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Triangle.cpp
*/
#include "Triangle.hpp"
#include <cmath>

using namespace RayTracer;
using namespace Math;

Triangle::Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2, std::shared_ptr<IMaterial> material) : _v0(v0), _v1(v1), _v2(v2), _material(std::move(material))
{}

bool Triangle::intersect(const Ray &ray, double &t, Point3D &hitPoint, Vector3D &normal) const
{
    const double EPS = 1e-8;
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;

    Vector3D P(
        ray.direction.y * edge2.z - ray.direction.z * edge2.y,
        ray.direction.z * edge2.x - ray.direction.x * edge2.z,
        ray.direction.x * edge2.y - ray.direction.y * edge2.x
    );

    double det = edge1.dot(P);
    if (std::fabs(det) < EPS)
        return false;

    double invDet = 1.0 / det;
    Vector3D T = ray.origin - _v0;
    double u = T.dot(P) * invDet;
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3D Q(
        T.y * edge1.z - T.z * edge1.y,
        T.z * edge1.x - T.x * edge1.z,
        T.x * edge1.y - T.y * edge1.x
    );

    double v = ray.direction.dot(Q) * invDet;
    if (v < 0.0 || u + v > 1.0)
        return false;

    double tTemp = edge2.dot(Q) * invDet;
    if (tTemp > EPS) {
        t = tTemp;
        hitPoint = ray.origin + ray.direction * t;

        Vector3D N(
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x
        );
        double len = N.length();
        normal = N / len;
        return true;
    }
    return false;
}

void Triangle::translate(const Vector3D &v)
{
    _v0 = _v0 + v;
    _v1 = _v1 + v;
    _v2 = _v2 + v;
}

void Triangle::rotate(const Vector3D &axis, double angleDegrees)
{
    Point3D center(_v0.x / 3.0 + _v1.x / 3.0 + _v2.x / 3.0,
                  _v0.y / 3.0 + _v1.y / 3.0 + _v2.y / 3.0,
                  _v0.z / 3.0 + _v1.z / 3.0 + _v2.z / 3.0);

    Vector3D v0Rel = _v0 - center;
    Vector3D v1Rel = _v1 - center;
    Vector3D v2Rel = _v2 - center;

    Vector3D v0Rot = rotateVector(v0Rel, axis, angleDegrees);
    Vector3D v1Rot = rotateVector(v1Rel, axis, angleDegrees);
    Vector3D v2Rot = rotateVector(v2Rel, axis, angleDegrees);

    _v0 = center + v0Rot;
    _v1 = center + v1Rot;
    _v2 = center + v2Rot;
}

void Triangle::setPosition(const Point3D &pos)
{
    Point3D center(_v0.x / 3.0 + _v1.x / 3.0 + _v2.x / 3.0,
                  _v0.y / 3.0 + _v1.y / 3.0 + _v2.y / 3.0,
                  _v0.z / 3.0 + _v1.z / 3.0 + _v2.z / 3.0);
    
    Vector3D translation = pos - center;
    
    translate(translation);
}

void Triangle::setVertices(const Point3D &v0, const Point3D &v1, const Point3D &v2)
{
    _v0 = v0;
    _v1 = v1;
    _v2 = v2;
}

void Triangle::setMaterial(std::shared_ptr<IMaterial> material)
{
    _material = std::move(material);
}

std::shared_ptr<IMaterial> Triangle::getMaterial() const
{
    return _material;
}

void Triangle::setRadius(double radius)
{
    (void)radius;
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create()
{
    return std::make_unique<RayTracer::Triangle>();
}
