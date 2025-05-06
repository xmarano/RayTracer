/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Triangle.cpp
*/
#include "../include/Triangle.hpp"
#include <cmath>

using namespace RayTracer;
using namespace Math;

Triangle::Triangle(const Point3D &v0, const Point3D &v1, const Point3D &v2, std::shared_ptr<IMaterial> material) : _v0(v0), _v1(v1), _v2(v2), _material(std::move(material))
{}

bool Triangle::intersect(const Ray &ray, double &t, Point3D &hitPoint, Vector3D &normalOut) const
{
    const double EPS = 1e-8;
    // Arêtes
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;

    // Calcul du cross produit P = dir × edge2
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

    // Calcul du cross Q = T × edge1
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

        // normale (non unitaire) : edge1 × edge2
        Vector3D N(
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x
        );
        double len = N.length();
        normalOut = N / len;
        return true;
    }
    return false;
}
