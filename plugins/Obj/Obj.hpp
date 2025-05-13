#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "../../include/IPrimitive.hpp"
#include "../../include/Math3D.hpp"
#include "../../include/IMaterial.hpp"

namespace RayTracer {
    class Obj : public IPrimitive {
    public:
        Obj();
        ~Obj() override = default;

        bool intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const override;
        void translate(const Math::Vector3D &v) override { _offset += v; }
        void rotate(const Math::Vector3D &axis, double angleDegrees) override {
            for (auto &p : _vertices)
                p = Math::Point3D() + Math::rotateVector(p - Math::Point3D(), axis, angleDegrees);
        }
        std::shared_ptr<IMaterial> getMaterial() const override { return _material; }

        void setPosition(const Math::Point3D &pos) override {
            _offset = Math::Vector3D(pos.x, pos.y, pos.z);
        }
        void setRadius(double) override {}
        void setMaterial(std::shared_ptr<IMaterial> material) override { _material = std::move(material); }
        void setPath(const std::string &path) override;

    private:
        struct Face { int v0, v1, v2; };
        std::vector<Math::Point3D> _vertices;
        std::vector<Face> _faces;
        Math::Vector3D _offset{0.0, 0.0, 0.0};
        std::shared_ptr<IMaterial> _material;

        bool intersectTriangle(const Ray &ray,
            const Math::Point3D &a,
            const Math::Point3D &b,
            const Math::Point3D &c,
            double &t, Math::Vector3D &normal) const;
    };
}

extern "C" std::unique_ptr<RayTracer::IPrimitive> create();