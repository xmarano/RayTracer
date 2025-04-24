/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#include "../include/ConfigParser.hpp"
#include "../include/Exception.hpp"

Config::Scene Config::parseScene(const std::string &file)
{
    libconfig::Config cfg;
    Config::Scene scene;
    cfg.setAutoConvert(true);

    try {
        cfg.readFile(file.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw RayTracerException("Error: Unable to read the configuration file");
    } catch (const libconfig::ConfigException &cfgex) {
        throw RayTracerException("Error: Invalid configuration file format");
    }
    cfg.lookupValue("camera.resolution.width", scene.camera.width);
    cfg.lookupValue("camera.resolution.height", scene.camera.height);
    cfg.lookupValue("camera.position.x", scene.camera.position.x);
    cfg.lookupValue("camera.position.y", scene.camera.position.y);
    cfg.lookupValue("camera.position.z", scene.camera.position.z);
    cfg.lookupValue("camera.rotation.x", scene.camera.rotation.x);
    cfg.lookupValue("camera.rotation.y", scene.camera.rotation.y);
    cfg.lookupValue("camera.rotation.z", scene.camera.rotation.z);
    cfg.lookupValue("camera.fieldOfView", scene.camera.fieldOfView);

    return scene;
}
