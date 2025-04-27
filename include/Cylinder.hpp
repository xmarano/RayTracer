/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cylinder.hpp
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math3D.hpp"
#include "IMaterial.hpp"
#include <memory>

namespace RayTracer {

    class Cylinder : public IPrimitive {
    public:
        Cylinder(const Math::Point3D &baseCenter,
                 double radius,
                 double height,
                 std::shared_ptr<IMaterial> material);
        ~Cylinder() override = default;

        bool hits(const Ray &ray) const override;
        void translate(const Math::Vector3D &v) override;
        void rotate(const Math::Vector3D &axis, double angleDegrees) override;
        std::shared_ptr<IMaterial> getMaterial() const override;

    private:
        Math::Point3D _baseCenter;
        double _radius;
        double _height;
        Math::Vector3D _axis;
        std::shared_ptr<IMaterial> _material;
    };

}

