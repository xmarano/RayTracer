/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** IPrimitive.hpp
*/

#pragma once
#include "Math3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

namespace RayTracer {

    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual bool hits(const Ray &ray) const = 0;
        virtual void translate(const Math::Vector3D &v) = 0;
        virtual const Color &getColor() const = 0;
    };
}
