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
#include "ILight.hpp"
#include "Camera.hpp"

namespace RayTracer {

    class Scene {
    public:
        Scene() noexcept;

        void addObject(std::shared_ptr<IPrimitive> obj);
        void addLight(std::unique_ptr<ILight> light);
        void setAmbientLight(std::unique_ptr<ILight> light);

        void setCamera(const Camera &cam);
        const Camera &getCamera() const;

        const std::vector<std::shared_ptr<IPrimitive>> &getObjects() const;
        const std::vector<std::unique_ptr<ILight>> &getLights() const;
        const std::unique_ptr<ILight> &getAmbient() const;
        
        void addPrimitiveByType(const std::string &type);


    private:
        std::vector<std::shared_ptr<IPrimitive>> _objects;
        std::vector<std::unique_ptr<ILight>> _lights;
        std::unique_ptr<ILight> _ambient;
        Camera _camera;
    };

}