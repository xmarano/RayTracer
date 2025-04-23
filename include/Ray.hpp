/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Ray.hpp
*/

#pragma once
#include "Math3D.hpp"

namespace RayTracer {
    class Ray {
    public:
        Math::Point3D origin;
        Math::Vector3D direction;

        Ray();
        Ray(Math::Point3D _origin, Math::Vector3D _direction);
    };
}
