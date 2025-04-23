/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Ray.cpp
*/

#include "../include/Ray.hpp"

RayTracer::Ray::Ray() : origin(), direction() {}

RayTracer::Ray::Ray(Math::Point3D _origin, Math::Vector3D _direction)
    : origin(_origin), direction(_direction) {}
