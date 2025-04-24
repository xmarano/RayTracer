/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Camera.cpp
*/

#include "../include/Camera.hpp"

RayTracer::Rectangle3D::Rectangle3D(): origin(), bottom_side(), left_side()
{}

RayTracer::Rectangle3D::Rectangle3D(Math::Point3D o, Math::Vector3D bs, Math::Vector3D ls) : origin(o), bottom_side(bs), left_side(ls)
{}

Math::Point3D RayTracer::Rectangle3D::pointAt(double u, double v) const { 
    return origin + (bottom_side * u) + (left_side * v);
}

RayTracer::Camera::Camera() : origin(0, 0, 0), screen()
{}

RayTracer::Camera::Camera(const Math::Point3D &orig, const RayTracer::Rectangle3D &scr) : origin(orig), screen(scr)
{}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const {
    Math::Point3D P = screen.pointAt(u, v);
    Math::Vector3D dir = P - origin;
    return Ray(origin, dir);
}
