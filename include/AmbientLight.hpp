/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** AmbientLight.hpp
*/
#include "ILight.hpp"

#pragma once

namespace RayTracer {
    class AmbientLight : public ILight {
        public:
            explicit AmbientLight(float intensity);

            Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const override;

        private:
            float _intensity;
    };
}
