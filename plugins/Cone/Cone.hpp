/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cone.hpp
*/
#include <memory>
#include "../../include/IPrimitive.hpp"
#include "../../include/Math3D.hpp"
#include "../../include/IMaterial.hpp"

#pragma once

namespace RayTracer {
    class Cone : public IPrimitive {
        public:
            Cone();
            ~Cone() override = default;

            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
            void translate(const Math::Vector3D &v) override;
            void rotate(const Math::Vector3D &axis, double angleDegrees) override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            void setHeight(double height) override;
            void setCoAxis(const Math::Vector3D &axis) override;

            void setPosition(const Math::Point3D &pos) override;
            void setRadius(double radius) override;
            void setMaterial(std::shared_ptr<IMaterial> material) override;

        private:
            Math::Point3D _apex;
            double _height;
            double _radius;
            Math::Vector3D _axis;
            std::shared_ptr<IMaterial> _material;
    };
}

extern "C" {
    RayTracer::IPrimitive* create();
}
