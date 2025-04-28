#include "PrimitiveFactory.hpp"
#include "Material.hpp" 
#include <stdexcept>

namespace RayTracer {

std::shared_ptr<IPrimitive> PrimitiveFactory::createPrimitive(const std::string &type) {
    auto defaultMaterial = std::make_shared<Material>();

    if (type == "sphere") {
        return std::make_shared<Sphere>(
            Math::Point3D(0.0, 0.0, 0.0),
            1.0,                 
            defaultMaterial           
        );
    } else if (type == "plane") {
        return std::make_shared<Plane>(
            Math::Point3D(0.0, 0.0, 0.0),  
            Math::Vector3D(0.0, 1.0, 0.0),
            defaultMaterial
        );
    } else if (type == "cone") {
        return std::make_shared<Cone>(
            Math::Point3D(0.0, 0.0, 0.0), // Apex
            1.0,                          // Hauteur
            0.5,                          // Angle
            defaultMaterial
        );
    } else if (type == "cylinder") {
        return std::make_shared<Cylinder>(
            Math::Point3D(0.0, 0.0, 0.0), // Base center
            1.0,                          // Hauteur
            0.5,                          // Rayon
            defaultMaterial
        );
    } else {
        throw std::invalid_argument("Unknown primitive type: " + type);
    }
}

}
