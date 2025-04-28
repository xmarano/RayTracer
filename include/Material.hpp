#pragma once

#include "IMaterial.hpp"
#include "Color.hpp" 

namespace RayTracer {

class Material : public IMaterial {
public:
    Material();
    ~Material() override = default;

    Color getBaseColor() const override;
    Color shade(const Color &base, const Color &light, const Math::Point3D &position) const override;

private:
    Color _baseColor;
};

}
