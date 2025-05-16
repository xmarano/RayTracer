/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** main.hpp
*/
#pragma once

#include "ConfigParser.hpp"
#include "IPrimitive.hpp"
#include "Display.hpp"
#include "Scene.hpp"
#include "Color.hpp"
#include "PluginLoader.hpp"
#include <thread>
#include <memory>
#include <vector>
#include <string>

RayTracer::PluginLoader loader;

class Main {
    public:
        void printHelp();
        void parseArguments(int argc, char **argv, std::string &file, bool &isDebug, bool &wantPPM);
        void debug_config(const Config::Scene &cfg);
        void calculPPM(const Config::Scene &cfg, Display &display, bool wantPPM);
        void addObjectsToScene(RayTracer::Scene &scene, const Config::Scene &cfg);
};

template <typename ConfigType, typename SetterFunc>
void addPrimitiveFromConfig(
    RayTracer::Scene &scene,
    const std::vector<ConfigType> &configs,
    const std::string &pluginName,
    SetterFunc setter)
{
    for (const auto &cfg : configs) {
        auto obj = loader.loadPrimitive(pluginName);
        setter(obj, cfg);
        obj->setMaterial(std::make_shared<RayTracer::FlatColor>(cfg.color));
        scene.addObject(std::move(obj));
    }
}

