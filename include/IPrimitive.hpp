/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** IPrimitive.hpp
*/
#pragma once

#include <memory>
#include "Math3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "IMaterial.hpp"

namespace RayTracer {
class IMaterial;
class IPrimitive {
public:
    virtual ~IPrimitive() = default;
    virtual bool hits(const Ray &ray) const = 0;
    virtual void translate(const Math::Vector3D &v) = 0;
    virtual void rotate(const Math::Vector3D &axis, double angleDegrees) = 0;
    virtual std::shared_ptr<IMaterial> getMaterial() const = 0;

    Color getBaseColor() const {
        return getMaterial()->getBaseColor();
    }
};
}