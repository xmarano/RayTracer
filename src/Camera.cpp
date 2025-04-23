/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Camera.cpp
*/

#include "../include/Camera.hpp"

using namespace RayTracer;

Rectangle3D::Rectangle3D() : origin(), bottom_side(), left_side() {}

Rectangle3D::Rectangle3D(Math::Point3D _o, Math::Vector3D _bs, Math::Vector3D _ls)
    : origin(_o), bottom_side(_bs), left_side(_ls) {}

Math::Point3D Rectangle3D::pointAt(double u, double v) const {
    return origin + (bottom_side * u) + (left_side * v);
}

Camera::Camera() : origin(0, 0, 0), screen() {}

Camera::Camera(const Math::Point3D &orig, const Rectangle3D &scr)
    : origin(orig), screen(scr) {}

Ray Camera::ray(double u, double v) const {
    Math::Point3D P = screen.pointAt(u, v);
    Math::Vector3D dir = P - origin;
    return Ray(origin, dir);
}
