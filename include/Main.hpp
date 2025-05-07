/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** main.hpp
*/
#include "ConfigParser.hpp"
#include "IPrimitive.hpp"
#include "Display.hpp"
#include "Scene.hpp"
#include <thread>

#pragma once

class Main {
    public:
        void printHelp();
        void parseArguments(int argc, char **argv, std::string &file, bool &isDebug, bool &wantPPM);
        void debug_config(const Config::Scene &cfg);
        void calculPPM(const Config::Scene &cfg, Display &display, bool wantPPM);
        void addObjectsToScene(RayTracer::Scene &scene, const Config::Scene &cfg);
};
