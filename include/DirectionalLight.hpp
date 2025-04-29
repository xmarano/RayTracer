/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** DirectionalLight.hpp
*/
#include "ILight.hpp"
#include "Math3D.hpp"

#pragma once

namespace RayTracer {
    class DirectionalLight : public ILight {
        public:
            DirectionalLight(const Math::Vector3D &direction, float intensity);
            Math::Vector3D getDirection() const;
            Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const override;

        private:
            Math::Vector3D _direction;
            float _intensity;
    };
}
