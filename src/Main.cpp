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
#include "../include/Material.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/Sphere.hpp"
#include "../include/Camera.hpp"
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
        bool is_ppm = (file.substr(file.find_last_of('.') + 1) == "ppm");
        if (!is_ppm && !is_valid_cfg(file))
            throw RayTracerException("Error: SCENE_FILE must have .cfg extension");

        if (is_ppm) {
            ppm(file);
            return 0;
        }

        // --- parse .cfg ---
        Config::Scene cfg = Config::parseScene(file);
        std::cout << "Camera: " << cfg.camera.width << "×" << cfg.camera.height << std::endl;
        std::cout << "POS=("
                  << cfg.camera.position.x << ","
                  << cfg.camera.position.y << ","
                  << cfg.camera.position.z << ")\n";
        std::cout << "ROT=("
                  << cfg.camera.rotation.x << ","
                  << cfg.camera.rotation.y << ","
                  << cfg.camera.rotation.z << ")\n";
        std::cout << "FOV=" << cfg.camera.fieldOfView << std::endl;

        // --- build scene ---
        RayTracer::Scene scene;

        // ambient light
        auto ambientLight = std::make_unique<RayTracer::AmbientLight>(0.2f);
        scene.setAmbientLight(std::move(ambientLight));

        // directional light
        auto dirLight = std::make_unique<RayTracer::DirectionalLight>(
            Math::Vector3D(-1.0, -1.0, -1.0), 0.8f
        );
        scene.addLight(std::move(dirLight));

        // --- flat-color material + sphere ---
        auto material = std::make_shared<RayTracer::FlatColor>(Color(255, 100, 100));
        std::cout << "Material base color = "
                  << material->getBaseColor().r << " "
                  << material->getBaseColor().g << " "
                  << material->getBaseColor().b << std::endl;

        auto sphere = std::make_shared<RayTracer::Sphere>(
            Math::Point3D(0, 0, -5),
            1.0,
            material
        );
        scene.addObject(sphere);

        // --- shoot a dummy ray at the sphere’s center ---
        Math::Point3D intersection(0, 0, -5);
        RayTracer::Ray ray(Math::Point3D(0, 0, 0), Math::Vector3D(0, 0, -1));

        // accumulate ambient contribution
        Color finalColor{0, 0, 0};
        if (scene.getAmbient())
            finalColor = scene.getAmbient()->illuminate(ray, *sphere, intersection);

        // accumulate directional contributions
        for (const auto &lightPtr : scene.getLights()) {
            Color contrib = lightPtr->illuminate(ray, *sphere, intersection);
            finalColor.r = std::min(finalColor.r + contrib.r, 255);
            finalColor.g = std::min(finalColor.g + contrib.g, 255);
            finalColor.b = std::min(finalColor.b + contrib.b, 255);
        }

        std::cout << "Final color at point = "
                  << finalColor.r << " "
                  << finalColor.g << " "
                  << finalColor.b << std::endl;

    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
