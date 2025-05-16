/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** PluginLoader.hpp
*/

#pragma once

#include <memory>
#include <string>
#include "IPrimitive.hpp"

namespace RayTracer {
    class PluginLoader {
        public:
            std::unique_ptr<IPrimitive> loadPrimitive(const std::string &soName);
    };
}
