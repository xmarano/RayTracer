/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Triangle.hpp
*/
#pragma once

#include "../../include/IPrimitive.hpp"
#include "../../include/Math3D.hpp"

namespace RayTracer {
    class Triangle : public IPrimitive {
        public:
            Triangle(const Math::Point3D &v0 = Math::Point3D(0, 0, 0),
                   const Math::Point3D &v1 = Math::Point3D(1, 0, 0), 
                   const Math::Point3D &v2 = Math::Point3D(0, 1, 0),
                   std::shared_ptr<IMaterial> material = nullptr);
            ~Triangle() override = default;

            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
            void translate(const Math::Vector3D &v) override;
            void rotate(const Math::Vector3D &axis, double angleDegrees) override;
            void setPosition(const Math::Point3D &pos) override;
            void setVertices(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2) override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            void setRadius(double radius) override;

        private:
            Math::Point3D _v0;
            Math::Point3D _v1;
            Math::Point3D _v2;
            std::shared_ptr<IMaterial> _material;
    };
}
