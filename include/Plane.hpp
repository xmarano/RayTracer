/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.hpp
*/

#pragma once

#include "Math3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    class Plane {
    public:
        Math::Point3D point;
        Math::Vector3D normal;
        Color color;

        Plane();
        Plane(const Math::Point3D &point, const Math::Vector3D &normal, const Color &color);

        bool hits(const Ray &ray) const;
    };
}
