/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.hpp
*/

#pragma once
#include "IPrimitive.hpp"

namespace RayTracer {

    class Plane : public IPrimitive {
    public:
        Math::Point3D point;
        Math::Vector3D normal;
        Color color;

        Plane(Math::Point3D point, Math::Vector3D normal, Color color);

        bool hits(const Ray &ray) const override;
        void translate(const Math::Vector3D &v) override;
        const Color &getColor() const override;
    };
}
