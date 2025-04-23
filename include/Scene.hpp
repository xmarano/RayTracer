/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Scene.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "IPrimitive.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "Camera.hpp"

namespace RayTracer {

    class Scene {
    public:
        std::vector<std::shared_ptr<IPrimitive>> objects;
        std::vector<DirectionalLight> directionalLights;
        AmbientLight ambient;
        Camera camera;

        Scene();

        void addObject(std::shared_ptr<IPrimitive> obj);
        void addDirectionalLight(const DirectionalLight &light);
        void setAmbientLight(const AmbientLight &light);
        void setCamera(const Camera &cam);
    };
}
