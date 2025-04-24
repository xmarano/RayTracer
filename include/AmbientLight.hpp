/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** AmbientLight.hpp
*/
#pragma once
#include "ILight.hpp"

namespace RayTracer {
    class AmbientLight : public ILight {
    public:
        explicit AmbientLight(float intensity);

        Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const override;

    private:
        float _intensity;
    };
}

