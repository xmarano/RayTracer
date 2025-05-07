/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.hpp
*/
#include <memory>
#include "../../include/IPrimitive.hpp"
#include "../../include/IMaterial.hpp"

#pragma once

namespace RayTracer {
    class Plane : public IPrimitive {
        public:
            Plane();
            Plane(const Math::Point3D &point, const Math::Vector3D &normal, std::shared_ptr<IMaterial> material);
            ~Plane() override = default;

            void translate(const Math::Vector3D &v) override;
            void rotate(const Math::Vector3D &axis, double angleDegrees) override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;

            void setPosition(const Math::Point3D &pos) override;
            void setRadius(double radius) override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;
            void setAxis(char axis) override;

        private:
            Math::Point3D _point;
            Math::Vector3D _normal;
            std::shared_ptr<IMaterial> _material;
    };
}

extern "C" {
    std::unique_ptr<RayTracer::IPrimitive> create();
}
