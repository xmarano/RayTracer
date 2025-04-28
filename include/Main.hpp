/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** main.hpp
*/
#include "ConfigParser.hpp"

#pragma once

class Main {
    public:
        void printHelp();
        void parseArguments(int argc, char **argv, std::string &file, bool &isPPM, bool &isDebug);
        void ppm(const std::string &file);
        void debug_config(const Config::Scene &cfg);
        void renderPPM(const Config::Scene &cfg);
};
