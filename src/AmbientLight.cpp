/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** AmbientLight.cpp
*/

#include "../include/AmbientLight.hpp"

RayTracer::AmbientLight::AmbientLight(float intensity)
  : _intensity(intensity)
{}

Color RayTracer::AmbientLight::illuminate(const Ray &, const IPrimitive &object, const Math::Point3D &) const
{
    Color base = object.getBaseColor();
    return Color(
        static_cast<int>(base.r * _intensity),
        static_cast<int>(base.g * _intensity),
        static_cast<int>(base.b * _intensity)
    );
}
