/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.hpp
*/
#include <memory>
#include "IPrimitive.hpp"

#pragma once

namespace RayTracer {
    class Sphere : public IPrimitive {
        public:
            Sphere(const Math::Point3D &center, double radius, std::shared_ptr<IMaterial> material);
            ~Sphere() override = default;
            void translate(const Math::Vector3D &v) override;
            void rotate(const Math::Vector3D &axis, double angleDegrees) override;
            std::shared_ptr<IMaterial> getMaterial() const override;
            bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;


        private:
            Math::Point3D _center;
            double _radius;
            std::shared_ptr<IMaterial> _material;
    };
}
