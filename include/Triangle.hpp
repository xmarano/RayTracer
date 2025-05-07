/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Triangle.hpp
*/
#include "IPrimitive.hpp"
#include "Math3D.hpp"

#pragma once

namespace RayTracer {
    class Triangle : public IPrimitive {
        public:
            Triangle(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2, std::shared_ptr<IMaterial> material);
            ~Triangle() override = default;

            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
            
            void translate(const Math::Vector3D &v) override { _v0 = _v0 + v; _v1 = _v1 + v; _v2 = _v2 + v; }

            void rotate(const Math::Vector3D &axis, double angleDegrees) override {
                _v0 = Math::Point3D() + Math::rotateVector(_v0 - Math::Point3D(), axis, angleDegrees);
                _v1 = Math::Point3D() + Math::rotateVector(_v1 - Math::Point3D(), axis, angleDegrees);
                _v2 = Math::Point3D() + Math::rotateVector(_v2 - Math::Point3D(), axis, angleDegrees);
            }

            std::shared_ptr<IMaterial> getMaterial() const override { return _material; }

        private:
            Math::Point3D _v0, _v1, _v2;
            std::shared_ptr<IMaterial> _material;
    };
}
