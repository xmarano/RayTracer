/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Cone.hpp
*/

#pragma once

#include "IPrimitive.hpp"
#include "Math3D.hpp"
#include "IMaterial.hpp"
#include <memory>

namespace RayTracer {

    class Cone : public IPrimitive {
    public:
        Cone(const Math::Point3D &apex,
             double height,
             double radius,
             std::shared_ptr<IMaterial> material);
        ~Cone() override = default;

        bool hits(const Ray &ray) const override;
        void translate(const Math::Vector3D &v) override;
        void rotate(const Math::Vector3D &axis, double angleDegrees) override;
        std::shared_ptr<IMaterial> getMaterial() const override;

    private:
        Math::Point3D _apex;
        double _height;
        double _radius;
        Math::Vector3D _axis;
        std::shared_ptr<IMaterial> _material;
    };

}
