/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.hpp
*/
#pragma once

#include <memory>
#include "../../include/IPrimitive.hpp"
#include "../../include/Math3D.hpp"
#include "../../include/IMaterial.hpp"

namespace RayTracer {
    class Cylinder : public IPrimitive {
    public:
        Cylinder();
        Cylinder(const Math::Point3D &baseCenter, double radius, double height, std::shared_ptr<IMaterial> material);
        ~Cylinder() override = default;

        bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
        void translate(const Math::Vector3D &v) override;
        void rotate(const Math::Vector3D &axis, double angleDegrees) override;
        std::shared_ptr<IMaterial> getMaterial() const override;

        void setPosition(const Math::Point3D &pos) override;
        void setRadius(double radius) override;
        void setMaterial(std::shared_ptr<IMaterial> material) override;


    private:
        Math::Point3D _baseCenter;
        double _radius;
        double _height;
        Math::Vector3D _axis;
        Math::Point3D _center;
        std::shared_ptr<IMaterial> _material;
    };
}

extern "C" {
    std::unique_ptr<RayTracer::IPrimitive> create();
}
