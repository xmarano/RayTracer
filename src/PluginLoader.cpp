/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** PluginLoader.cpp
*/


#include "../include/PluginLoader.hpp"
#include "../include/Exception.hpp"
#include <dlfcn.h>

using RayTracer::IPrimitive;

std::unique_ptr<IPrimitive> loadPrimitive(const std::string &soName)
{
    void *handle = dlopen(("./plugins/" + soName).c_str(), RTLD_LAZY);
    if (!handle)
        throw RayTracerException("Cannot open plugin: " + std::string(dlerror()));

    using CreateFunc = std::unique_ptr<IPrimitive>(*)();
    CreateFunc create = reinterpret_cast<CreateFunc>(dlsym(handle, "create"));
    if (!create)
        throw RayTracerException("Cannot find create function: " + std::string(dlerror()));

    return create();
}
