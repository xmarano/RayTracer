/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** IPrimitive.hpp
*/
#include <memory>
#include "Math3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "IMaterial.hpp"

#pragma once

namespace RayTracer {
    class IMaterial;
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual void translate(const Math::Vector3D &v) = 0;
            virtual void rotate(const Math::Vector3D &axis, double angleDegrees) = 0;
            virtual std::shared_ptr<IMaterial> getMaterial() const = 0;
            virtual bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const = 0;

            Color getBaseColor() const {
                return getMaterial()->getBaseColor();
            }
    };
}
