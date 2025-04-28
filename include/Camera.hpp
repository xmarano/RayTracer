/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Camera.hpp
*/
#include "Math3D.hpp"
#include "Ray.hpp"

#pragma once

namespace RayTracer {
    class Rectangle3D {
        public:
            Math::Point3D origin;
            Math::Vector3D bottom_side;
            Math::Vector3D left_side;

            Rectangle3D();
            Rectangle3D(Math::Point3D _o, Math::Vector3D _bs, Math::Vector3D _ls);
            Math::Point3D pointAt(double u, double v) const;
    };

    class Camera {
        public:
            Math::Point3D origin;
            Rectangle3D screen;

            Camera();
            Camera(const Math::Point3D &orig, const Rectangle3D &scr);
            Ray ray(double u, double v) const;
    };
}
