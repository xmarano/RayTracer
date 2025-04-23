/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** AmbientLight.hpp
*/

#pragma once

namespace RayTracer {
    class AmbientLight {
    public:
        float intensity;

        AmbientLight(float i = 0.1f) : intensity(i) {}
    };
}
