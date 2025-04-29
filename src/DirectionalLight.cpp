/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** DirectionalLight.cpp
*/
#include "../include/DirectionalLight.hpp"
#include <algorithm>

RayTracer::DirectionalLight::DirectionalLight(const Math::Vector3D &direction, float intensity) : _direction(direction), _intensity(intensity)
{}

Color RayTracer::DirectionalLight::illuminate(const Ray &, const IPrimitive &object, const Math::Point3D &point) const
{
    (void)point;
    Color base = object.getBaseColor();
    return Color(
        static_cast<int>(std::clamp(base.r * _intensity, 0.0f, 255.0f)),
        static_cast<int>(std::clamp(base.g * _intensity, 0.0f, 255.0f)),
        static_cast<int>(std::clamp(base.b * _intensity, 0.0f, 255.0f))
    );
}

Math::Vector3D RayTracer::DirectionalLight::getDirection() const
{
    return _direction;
}
