/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.hpp
*/
#include "IPrimitive.hpp"
#include "Math3D.hpp"
#include "IMaterial.hpp"
#include <memory>

#pragma once

namespace RayTracer {
    class Cylinder : public IPrimitive {
        public:
            Cylinder(const Math::Point3D &baseCenter, double radius, double height, std::shared_ptr<IMaterial> material);
            ~Cylinder() override = default;

            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
            void translate(const Math::Vector3D &v) override;
            void rotate(const Math::Vector3D &axis, double angleDegrees) override;
            std::shared_ptr<IMaterial> getMaterial() const override;

        private:
            Math::Point3D _baseCenter;
            double _radius;
            double _height;
            Math::Vector3D _axis;
            std::shared_ptr<IMaterial> _material;
            Math::Point3D _center;
    };
}
