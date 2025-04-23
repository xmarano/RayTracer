/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.hpp
*/


#pragma once

#include "IPrimitive.hpp"

namespace RayTracer {

    class Sphere : public IPrimitive {
    public:
        Math::Point3D center;
        double radius;
        Color color;

        Sphere(Math::Point3D center, double radius, Color color);

        bool hits(const Ray &ray) const override;
        void translate(const Math::Vector3D &v) override;
        const Color &getColor() const override;
    };
}

