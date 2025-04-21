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

int main(int argc, char **argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--coverage") {
            return system("make tests_run");
        }
        if (argc != 2)
            throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");
        std::string file = argv[1];
        if (!is_valid_cfg(file))
            throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
        std::cout << "Parsing scene: " << file << std::endl;
    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
