/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#include <vector>
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

#pragma once

namespace Config {

    // class Color {
    //     public:
    //         int r, g, b;
    //         Color(): r(0), g(0), b(0) {}
    //         Color(int rr, int gg, int bb): r(rr), g(gg), b(bb) {}
    // };

    class Camera {
        public:
            int width;
            int height;
            Math::Point3D position;
            int position_x;
            int position_y;
            int position_z;
            Math::Vector3D rotation;
            double fieldOfView;

            Camera() : width(0), height(0) , position(), rotation() , fieldOfView(0.0) {}
    };

    // class Sphere {
    //     public:
    //         Math::Point3D center;
    //         double radius;
    //         Color color;
    //         Sphere() : center(), radius(0.0), color() {}
    // };

    // class Plane {
    //     public:
    //         char axis;
    //         double position;
    //         Color color;
    //         Plane() : axis('Z'), position(0.0), color() {}
    // };

    // class PointLight {
    //     public:
    //         Math::Point3D position;
    //         Color color;
    //         PointLight(): position(), color() {}
    // };

    // class DirLight {
    //     public:
    //         Math::Vector3D direction;
    //         Color color;
    //         DirLight(): direction(), color() {}
    // };

    class Scene {
        public:
            Camera camera;
            // std::vector<Sphere> spheres;
            // std::vector<Plane> planes;
            // double ambient;
            // double diffuse;
            // std::vector<PointLight> points;
            // std::vector<DirLight> directionals;

            // Scene(): ambient(0.0), diffuse(0.0) {}
    };

    Scene parseScene(const std::string &path);
}
