/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Scene.cpp
*/
#include "../include/Scene.hpp"
#include "../include/PrimitiveFactory.hpp"

RayTracer::Scene::Scene() noexcept
    : _objects(), _lights(), _ambient(nullptr)
{}

void RayTracer::Scene::addObject(std::shared_ptr<RayTracer::IPrimitive> obj)
{
    _objects.push_back(std::move(obj));
}

void RayTracer::Scene::addLight(std::unique_ptr<RayTracer::ILight> light)
{
    _lights.push_back(std::move(light));
}

void RayTracer::Scene::setAmbientLight(std::unique_ptr<RayTracer::ILight> light)
{
    _ambient = std::move(light);
}

const std::vector<std::shared_ptr<RayTracer::IPrimitive> >&
RayTracer::Scene::getObjects() const
{
    return _objects;
}

const std::vector<std::unique_ptr<RayTracer::ILight> >&
RayTracer::Scene::getLights() const
{
    return _lights;
}

const std::unique_ptr<RayTracer::ILight>&
RayTracer::Scene::getAmbient() const
{
    return _ambient;
}

void RayTracer::Scene::setCamera(const Camera &cam)
{
    _camera = cam;
}

const RayTracer::Camera& RayTracer::Scene::getCamera() const
{
    return _camera;
}

void RayTracer::Scene::addPrimitiveByType(const std::string &type)
{
    try {
        auto primitive = RayTracer::PrimitiveFactory::createPrimitive(type);
        addObject(primitive);
    } catch (const std::exception &e) {
    }
}

