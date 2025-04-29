/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** main.hpp
*/
#pragma once
#include "ILight.hpp"
#include "Math3D.hpp"

namespace RayTracer {
    class PointLight : public ILight {
    public:
        PointLight(const Math::Point3D &pos, float intensity);

        Color illuminate(const Ray &ray, const IPrimitive &object, const Math::Point3D &point) const override;
        const Math::Point3D &getPosition() const;

    private:
        Math::Point3D _position;
        float _intensity;
    };
}
