/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Sphere.hpp
*/
#pragma once
#include <memory>
#include "IPrimitive.hpp"
namespace RayTracer {
class Sphere : public IPrimitive {
public:
    Sphere(const Math::Point3D &center,
           double radius,
           std::shared_ptr<IMaterial> material);
    ~Sphere() override = default;
    bool hits(const Ray &ray) const override;
    void translate(const Math::Vector3D &v) override;
    std::shared_ptr<IMaterial> getMaterial() const override;

private:
    Math::Point3D              _center;
    double                     _radius;
    std::shared_ptr<IMaterial> _material;
};
}
