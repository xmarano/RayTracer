/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** DirectionalLight.hpp
*/

#pragma once
#include "Math3D.hpp"

namespace RayTracer {
    class DirectionalLight {
    public:
        Math::Vector3D direction;
        float intensity;

        DirectionalLight(Math::Vector3D dir = {0, -1, 0}, float i = 1.0f)
            : direction(dir), intensity(i) {}
    };
}
