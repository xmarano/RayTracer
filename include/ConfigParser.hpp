/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** OOP
*/
#include <vector>
#include <limits>
#ifdef __APPLE__
#include </opt/homebrew/include/libconfig.h++>
#elif __linux__
#include </usr/include/libconfig.h++>
#endif
#include "Math3D.hpp"
#include "Color.hpp"

#pragma once

namespace Config {
    class Camera {
        public:
            int width;
            int height;
            Math::Point3D position;
            Math::Vector3D rotation;
            double fieldOfView;

            Camera() : width(0), height(0) , position(), rotation() , fieldOfView(0.0) {}
    };

    class Sphere {
        public:
            Math::Point3D center;
            double radius;
            Color color;
            Sphere() : center(), radius(0.0), color() {}
    };

    class Plane {
        public:
            char axis;
            double position;
            Color color;
            Plane() : axis('Z'), position(0.0), color() {}
    };

    class Point {
        public:
            Math::Point3D position;
            Point(): position() {}
    };

    class Directional {
        public:
            Math::Vector3D direction;
            Directional(): direction() {}
    };

    class Scene {
        public:
            Camera camera;
            std::vector<Sphere> spheres;
            std::vector<Plane> planes;
            double ambient;
            double diffuse;
            std::vector<Point> points;
            std::vector<Directional> directionals;

            // Scene(): ambient(0.0), diffuse(0.0) {}
    };

    Scene parseScene(const std::string &path);
}
