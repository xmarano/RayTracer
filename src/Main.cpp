/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/
#include <iostream>
#include <string>
#include <memory>
#include <utility> 
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/Sphere.hpp"
#include "../include/Scene.hpp"

void ppm(const std::string &file)
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
        if (argc != 2)
            throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");

        std::string file = argv[1];
        int is_ppm = file.substr(file.find_last_of(".") + 1) == "ppm";
        if (!is_ppm && !is_valid_cfg(file))
            throw RayTracerException("Error: SCENE_FILE must have .cfg extension");

        if (is_ppm) {
            ppm(file);
            return 0;
        }

        // Chargement scène
        Config::Scene configScene = Config::parseScene(file);
        std::cout << "Camera: "<< configScene.camera.width  << "×"<< configScene.camera.height << std::endl;
        std::cout << "POS=(" << configScene.camera.position.x << "," << configScene.camera.position.y << "," << configScene.camera.position.z << ")\n";
        std::cout << "ROT=(" << configScene.camera.rotation.x << "," << configScene.camera.rotation.y << "," << configScene.camera.rotation.z << ")\n";
        std::cout << "FOV=" << configScene.camera.fieldOfView << std::endl;

        // Initialisation scène réelle
        RayTracer::Scene scene;

        auto ambient = std::make_unique<RayTracer::AmbientLight>(0.2f);
        scene.setAmbientLight(std::move(ambient));
        auto dirLight = std::make_unique<RayTracer::DirectionalLight>(
            Math::Vector3D(-1.0, -1.0, -1.0), 0.8f
        );
        scene.addLight(std::move(dirLight));
        auto sphere = std::make_shared<RayTracer::Sphere>(
            Math::Point3D(0, 0, -5), 1.0, Color(255, 100, 100)
        );
        scene.addObject(sphere);
        Math::Point3D intersection(0, 0, -5);
        RayTracer::Ray dummyRay(Math::Point3D(0, 0, 0), Math::Vector3D(0, 0, -1));
        Color finalColor(0, 0, 0);
        if (scene.getAmbient())
            finalColor = scene.getAmbient()->illuminate(dummyRay, *sphere, intersection);

        for (const auto &light : scene.getLights()) {
            Color add = light->illuminate(dummyRay, *sphere, intersection);
            finalColor.r = std::min(finalColor.r + add.r, 255);
            finalColor.g = std::min(finalColor.g + add.g, 255);
            finalColor.b = std::min(finalColor.b + add.b, 255);
        }

        std::cout << "Final color at point = " << finalColor.r << " " << finalColor.g << " " << finalColor.b << std::endl;

    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
