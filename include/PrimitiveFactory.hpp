#pragma once

#include "IPrimitive.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include <memory>
#include <string>

namespace RayTracer {

class PrimitiveFactory {
public:
    static std::shared_ptr<IPrimitive> createPrimitive(const std::string &type);
};

} // namespace RayTracer
