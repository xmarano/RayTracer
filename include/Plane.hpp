/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Plane.hpp
*/
#pragma once
#include <memory>
#include "IPrimitive.hpp"

namespace RayTracer {

class Plane : public IPrimitive {
public:
    Plane(const Math::Point3D &point,
          const Math::Vector3D &normal,
          std::shared_ptr<IMaterial> material);
    ~Plane() override = default;

    bool hits(const Ray &ray) const override;
    void translate(const Math::Vector3D &v) override;
    void rotate(const Math::Vector3D &axis, double angleDegrees) override;
    std::shared_ptr<IMaterial> getMaterial() const override;

private:
    Math::Point3D              _point;
    Math::Vector3D             _normal;
    std::shared_ptr<IMaterial> _material;
};
}
