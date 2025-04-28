/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Material.cpp
*/

#include "Material.hpp"

namespace RayTracer {

Material::Material()
    : _baseColor(1.0, 1.0, 1.0) // Couleur blanche par défaut
{
}

Color Material::getBaseColor() const
{
    return _baseColor;
}

Color Material::shade(const Color &base, const Color &light, const Math::Point3D &position) const
{
    (void)position; // pour éviter le warning si position est inutilisée
    // Simple shading = multiplication composante par composante
    return Color(base.r * light.r, base.g * light.g, base.b * light.b);
}

}
