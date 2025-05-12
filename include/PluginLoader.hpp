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

std::unique_ptr<RayTracer::IPrimitive> loadPrimitive(const std::string &soName);
