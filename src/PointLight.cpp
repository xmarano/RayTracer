/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** PointLight.cpp
*/
#include "../include/PointLight.hpp"

RayTracer::PointLight::PointLight(const Math::Point3D &pos, float intensity) : _position(pos), _intensity(intensity)
{}

Color RayTracer::PointLight::illuminate(const Ray &, const IPrimitive &object, const Math::Point3D &point) const
{
    Color base = object.getBaseColor();
    Math::Vector3D lightVec = _position - point;
    double distance = lightVec.length();
    double attenuation = 1.0 / (distance * distance);

    return Color(
        std::clamp(static_cast<int>(base.r * _intensity * attenuation), 0, 255),
        std::clamp(static_cast<int>(base.g * _intensity * attenuation), 0, 255),
        std::clamp(static_cast<int>(base.b * _intensity * attenuation), 0, 255)
    );
}

const Math::Point3D &RayTracer::PointLight::getPosition() const
{
    return _position;
}
