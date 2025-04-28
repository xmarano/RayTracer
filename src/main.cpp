/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/
#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <utility>
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"
#include "../include/IMaterial.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/Sphere.hpp"
#include "../include/Camera.hpp"
#include "../include/Scene.hpp"

static void printHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    std::cout << "  SCENE_FILE: scene configuration\n";
}

static void parseArguments(int argc, char **argv, std::string &file, bool &isPPM)
{
    if (argc == 2 && std::string(argv[1]) == "unitest")
        std::exit(0);
    if (argc == 2 && std::string(argv[1]) == "-help") {
        printHelp();
        std::exit(0);
    }
    if (argc != 2)
        throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");

    file = argv[1];
    isPPM = (file.substr(file.find_last_of('.') + 1) == "ppm");
    if (!isPPM && !is_valid_cfg(file))
        throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
}

void ppm(const std::string &file)
{
    Display display;
    display.parseFile(file);
    std::cout << "PPM size: " << display.getWidth()
              << "×" << display.getHeight() << std::endl;
    display.init();
    display.run();
}

void tmp_config(const Config::Scene &cfg)
{
    std::cout << "CAMERA:\n";
    std::cout << "resolution: " << cfg.camera.width
              << "×" << cfg.camera.height << std::endl;
    std::cout << "position=(" << cfg.camera.position.x
              << "," << cfg.camera.position.y
              << "," << cfg.camera.position.z << ")\n";
    std::cout << "rotation=(" << cfg.camera.rotation.x
              << "," << cfg.camera.rotation.y
              << "," << cfg.camera.rotation.z << ")\n";
    std::cout << "fieldOfView=" << cfg.camera.fieldOfView << std::endl << std::endl;
    std::cout << "SPHERES:\n";
    for (const auto &s : cfg.spheres)
        std::cout << "centre=(" << s.center.x << "," << s.center.y
                  << "," << s.center.z << ") rayon="
                  << s.radius << " couleur=(" << s.color.r << ","
                  << s.color.g << "," << s.color.b << ")\n";
    std::cout << "PLANES:\n";
    for (const auto &p : cfg.planes)
        std::cout << "axe=" << p.axis << " pos=" << p.position
                  << " couleur=(" << p.color.r << "," << p.color.g
                  << "," << p.color.b << ")\n";
    std::cout << "LIGHTS:\nambient=" << cfg.ambient
              << " diffuse=" << cfg.diffuse << "\n";
}

static void setupScene(const Config::Scene &cfg, RayTracer::Scene &scene, Math::Vector3D &lightDirNorm, std::shared_ptr<RayTracer::IPrimitive> &target)
{
    float aspect = static_cast<float>(cfg.camera.width)
                 / cfg.camera.height;
    float scale = std::tan((cfg.camera.fieldOfView * 0.5f)
                           * M_PI / 180.0f);
    Math::Vector3D bs{2 * scale * aspect, 0, 0};
    Math::Vector3D ls{0, 2 * scale, 0};
    Math::Point3D origin{
        cfg.camera.position.x - bs.x / 2,
        cfg.camera.position.y - ls.y / 2,
        cfg.camera.position.z - 1
    };
    scene.setCamera(RayTracer::Camera(
        cfg.camera.position,
        RayTracer::Rectangle3D(origin, bs, ls)
    ));
    scene.setAmbientLight(
        std::make_unique<RayTracer::AmbientLight>(0.2f)
    );
    Math::Vector3D dir{-1.0, -1.0, -1.0};
    float len = dir.length();
    lightDirNorm = {dir.x / len, dir.y / len, dir.z / len};
    scene.addLight(
        std::make_unique<RayTracer::DirectionalLight>(
            lightDirNorm, 0.8f
        )
    );
    auto mat = std::make_shared<RayTracer::FlatColor>(Color(255, 100, 100));
    target = std::make_shared<RayTracer::Sphere>(
        Math::Point3D(0, 0, -5), 1.0, mat
    );
    scene.addObject(target);
    std::cout << "Material base color = " << mat->getBaseColor().r << " " << mat->getBaseColor().g << " " << mat->getBaseColor().b << std::endl;
}

static Color computeColor(const RayTracer::Scene &scene, const std::shared_ptr<RayTracer::IPrimitive> &obj, const RayTracer::Ray &viewRay,
                          const Math::Point3D &pt,
                          const Math::Vector3D &lightDir)
{
    Color col{0, 0, 0};
    if (scene.getAmbient())
        col = scene.getAmbient()->illuminate(viewRay, *obj, pt);
    const float eps = 1e-4f;
    int i = 0;
    for (const auto &light : scene.getLights()) {
        RayTracer::Ray shadow;
        shadow.origin = {
            pt.x + lightDir.x * eps,
            pt.y + lightDir.y * eps,
            pt.z + lightDir.z * eps
        };
        shadow.direction = lightDir;
        bool inShadow = false;
        for (const auto &o : scene.getObjects()) {
            if (o.get() == obj.get())
                continue;
            if (o->hits(shadow)) {
                inShadow = true;
                break;
            }
        }
        std::cout << "Light " << i << (inShadow ? " is in shadow\n" : " is lit\n");
        if (!inShadow) {
            Color d = light->illuminate(viewRay, *obj, pt);
            col.r = std::min(col.r + d.r, 255);
            col.g = std::min(col.g + d.g, 255);
            col.b = std::min(col.b + d.b, 255);
        }
        ++i;
    }
    return col;
}

int main(int argc, char **argv)
{
    try {
        std::string file;
        bool isPPM = false;
        parseArguments(argc, argv, file, isPPM);
        if (isPPM) {
            ppm(file);
            return 0;
        }
        Config::Scene configScene = Config::parseScene(file);
        tmp_config(configScene);
        std::cout << "---------" << std::endl;
        RayTracer::Scene scene;
        Math::Vector3D lightDir;
        std::shared_ptr<RayTracer::IPrimitive> sphere;
        setupScene(configScene, scene, lightDir, sphere);

        Math::Point3D intersection{0, 0, -5};
        RayTracer::Ray viewRay(Math::Point3D(0, 0, 0), Math::Vector3D(0, 0, -1));
        Color final = computeColor(scene, sphere, viewRay, intersection, lightDir);

        std::cout << "Final color at point = "
                  << final.r << " "
                  << final.g << " "
                  << final.b << std::endl;
    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
