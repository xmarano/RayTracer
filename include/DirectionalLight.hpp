/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** DirectionalLight.hpp
*/
#pragma once
#include "ILight.hpp"
#include "Math3D.hpp"

namespace RayTracer {
    class DirectionalLight : public ILight {
    public:
        DirectionalLight(const Math::Vector3D &direction, float intensity);

        Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const override;

    private:
        Math::Vector3D _direction;
        float _intensity;
    };
}
