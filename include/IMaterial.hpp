/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Material.hpp
*/
#include "Color.hpp"
#include "Math3D.hpp"

#pragma once

namespace RayTracer {
    class IMaterial {
        public:
            virtual ~IMaterial() = default;
            virtual Color getBaseColor() const = 0;
            virtual Color shade(const Color &base, const Color &light, const Math::Point3D &point) const = 0;
    };

    class FlatColor : public IMaterial {
        public:
            explicit FlatColor(const Color &c) : _color(c) {}
            ~FlatColor() override = default;

            Color getBaseColor() const override { return _color; }
            Color shade(const Color & , const Color &light, const Math::Point3D &) const override { return light; }

        private:
            Color _color;
    };
}
