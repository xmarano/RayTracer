/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#include <iostream>
#include <string>
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"

void temp(const std::string &file)
{
    Display display;
    display.parseFile(file);
    std::cout << "PPM size: " << display.getWidth() << "×" << display.getHeight() << "\n";
    display.init();
    display.run();
}

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "unitest")
        return 0;
    if (argc == 2 && std::string(argv[1]) == "-help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>\n";
        std::cout << "  SCENE_FILE: scene configuration\n";
        return 0;
    }
    try {
        if (argc != 2)
            throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");
        std::string file = argv[1];
        if ((file != "scenes/demo.ppm") && !(is_valid_cfg(file)))
            throw RayTracerException("Error: SCENE_FILE must have .cfg extension");

            temp(file);
    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
