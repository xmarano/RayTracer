/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** ILight.hpp
*/
#include "Ray.hpp"
#include "Color.hpp"
#include "IPrimitive.hpp"

#pragma once

namespace RayTracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const = 0;
    };
}
