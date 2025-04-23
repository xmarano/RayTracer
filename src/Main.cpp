/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/

#include <iostream>
#include <string>
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"

void temp(const std::string &file)
{
    Display display;
    display.parseFile(file);
    std::cout << "PPM size: " << display.getWidth() << "×" << display.getHeight() << std::endl;
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
        if (argc != 2) {
            throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");
        }
        std::string file = argv[1];
        if ((file != "scenes/demo.ppm") && !(is_valid_cfg(file))) {
            throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
        }

        Config::Scene scene = Config::parseScene(file);
        std::cout << "Camera: "<< scene.camera.width  << "×"<< scene.camera.height << std::endl;
        std::cout << "POS=(" << scene.camera.position.x << "," << scene.camera.position.y << "," << scene.camera.position.z << ")\n";
        std::cout << "ROT=(" << scene.camera.rotation.x << "," << scene.camera.rotation.y << "," << scene.camera.rotation.z << ")\n";
        std::cout << "FOV=" << scene.camera.fieldOfView << std::endl;

        // temp(file);
    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
