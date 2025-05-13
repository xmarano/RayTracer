/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** OOP
*/
#pragma once

#include <vector>
#include <limits>
#include <string>
#ifdef __APPLE__
#include </opt/homebrew/include/libconfig.h++>
#elif __linux__
#include </usr/include/libconfig.h++>
#endif
#include "Math3D.hpp"
#include "Color.hpp"

namespace Config {
    class Camera {
    public:
        int width;
        int height;
        Math::Point3D position;
        Math::Vector3D rotation;
        double fieldOfView;

        Camera() : width(0), height(0), position(), rotation(), fieldOfView(0.0) {}
    };

    class Sphere {
    public:
        Math::Point3D center;
        double radius;
        Color color;
        Sphere() : center(), radius(0.0), color() {}
    };

    class Cylinder {
    public:
        Math::Point3D base;
        Math::Vector3D axis;
        double radius;
        double height;
        Color color;

        Cylinder() : base(), axis(), radius(0.0), height(0.0), color() {}
    };

    class Cone {
    public:
        Math::Point3D apex;
        Math::Vector3D axis;
        double radius;
        double height;
        Color color;

        Cone() : apex(), axis(), radius(0.0), height(0.0), color() {}
    };

    class Triangle {
    public:
        Math::Point3D a;
        Math::Point3D b;
        Math::Point3D c;
        Color color;

        Triangle() : a(), b(), c(), color() {}
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
        Point() : position() {}
    };

    class Directional {
    public:
        Math::Vector3D direction;
        Directional() : direction() {}
    };

    class ObjFile {
    public:
        std::string path;
        Math::Vector3D translation;
        Math::Vector3D rotation;
        Color color;

        ObjFile() : path(""), translation(), rotation(), color() {}
    };

    class Scene {
    public:
        Camera camera;
        std::vector<Sphere> spheres;
        std::vector<Cylinder> cylinders;
        std::vector<Cone> cones;
        std::vector<Triangle> triangles;
        std::vector<Plane> planes;
        std::vector<ObjFile> objs;
        double ambient;
        double diffuse;
        std::vector<Point> points;
        std::vector<Directional> directionals;
    };

    Scene parseScene(const std::string &path);
}
