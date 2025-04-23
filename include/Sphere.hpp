/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.hpp
*/


#pragma once
#include "Math3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    class Sphere {
    public:
        Math::Point3D center;
        double radius;
        Color color;

        Sphere(Math::Point3D _center, double _radius, Color _color);
        bool hits(const Ray &ray);
    };
}
