/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/
#include <thread>
#include <cmath>
#include <algorithm>
#include <limits>
#include "../include/Main.hpp"
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"
#include "../include/IMaterial.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/PointLight.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plane.hpp"
#include "../include/Camera.hpp"
#include "../include/Scene.hpp"


void Main::printHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE> [-d] [-w]\n";
    std::cout << "  SCENE_FILE: scene configuration (.cfg)\n";
    std::cout << "  -d : debug mode (print config)\n";
    std::cout << "  -w : write PPM to stdout (no window)\n";
}

void Main::parseArguments(int argc, char **argv, std::string &file, bool &isDebug, bool &wantPPM)
{
    if (argc == 2 && std::string(argv[1]) == "unitest")
        std::exit(0);

    if (argc == 2 && std::string(argv[1]) == "-help") {
        printHelp();
        std::exit(0);
    }

    if (argc == 3 && std::string(argv[2]) == "-d") {
        file = argv[1];
        isDebug = true;
        return;
    }

    if (argc == 3 && std::string(argv[2]) == "-w") {
        wantPPM = true;
    }

    if (argc != 2 && !wantPPM) {
        throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");
    } else if (argc == 3 && std::string(argv[2]) == "-d") {
        
    }

    file = argv[1];
    if (!is_valid_cfg(file)) {
        throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
    }
}

void Main::debug_config(const Config::Scene &cfg)
{
    std::cout << "CAMERA:\n";
    std::cout << "resolution: " << cfg.camera.width << " × " << cfg.camera.height << std::endl;
    std::cout << "position = (" << cfg.camera.position.x << ", " << cfg.camera.position.y << ", " << cfg.camera.position.z << ")\n";
    std::cout << "rotation = (" << cfg.camera.rotation.x << ", " << cfg.camera.rotation.y << ", " << cfg.camera.rotation.z << ")\n";
    std::cout << "fieldOfView = " << cfg.camera.fieldOfView << std::endl << std::endl;

    std::cout << "SPHERES:\n";
    for (const auto &s : cfg.spheres) {
        std::cout << "centre = (" << s.center.x << ", " << s.center.y << ", " << s.center.z << ")"
                  << "  rayon = " << s.radius
                  << "  couleur = (" << s.color.r << ", " << s.color.g << ", " << s.color.b << ")\n";
    }

    std::cout << "PLANES:\n";
    for (const auto &p : cfg.planes) {
        std::cout << "axe = '" << p.axis << "'"
                  << "  position = " << p.position
                  << "  couleur = (" << p.color.r << ", " << p.color.g << ", " << p.color.b << ")\n";
    }

    std::cout << "LIGHTS:\n";
    std::cout << "ambient = " << cfg.ambient
              << "  diffuse = " << cfg.diffuse << "\n";
}

void Main::calculPPM(const Config::Scene &cfg, Display &display, bool wantPPM)
{
    RayTracer::Scene scene;

    float aspect = static_cast<float>(cfg.camera.width) / cfg.camera.height;
    float scale  = std::tan((cfg.camera.fieldOfView * 0.5f) * M_PI / 180.0f);
    Math::Vector3D bs{-2.0f * scale * aspect, 0.0f, 0.0f};
    Math::Vector3D ls{0.0f, -2.0f * scale, 0.0f};
    Math::Point3D origin{
        cfg.camera.position.x - bs.x * 0.5f,
        cfg.camera.position.y - ls.y * 0.5f,
        cfg.camera.position.z - 1.0f
    };

    scene.setCamera(
        RayTracer::Camera(
            cfg.camera.position,
            RayTracer::Rectangle3D(origin, bs, ls)
        )
    );

    scene.setAmbientLight(
        std::make_unique<RayTracer::AmbientLight>(
            static_cast<float>(cfg.ambient)
        )
    );

    // Add lights
    for (const auto &d : cfg.directionals) {
        scene.addLight(
            std::make_unique<RayTracer::DirectionalLight>(
                d.direction,
                static_cast<float>(cfg.diffuse)
            )
        );
    }

    // Add point lights
    for (const auto &p : cfg.points) {
        scene.addLight(
            std::make_unique<RayTracer::PointLight>(
                p.position,
                static_cast<float>(cfg.diffuse)
            )
        );
    }

    for (const auto &s : cfg.spheres) {
        scene.addObject(
            std::make_shared<RayTracer::Sphere>(
                s.center,
                s.radius,
                std::make_shared<RayTracer::FlatColor>(s.color)
            )
        );
    }

    for (const auto &p : cfg.planes) {
        Math::Vector3D normal{0.0f, 0.0f, 0.0f};
        if (p.axis == 'X') normal.x = 1.0f;
        else if (p.axis == 'Y') normal.y = 1.0f;
        else normal.z = 1.0f;

        Math::Point3D pt{0.0f, 0.0f, 0.0f};
        if (p.axis == 'X') pt.x = p.position;
        else if (p.axis == 'Y') pt.y = p.position;
        else pt.z = p.position;

        scene.addObject(
            std::make_shared<RayTracer::Plane>(
                pt,
                normal,
                std::make_shared<RayTracer::FlatColor>(p.color)
            )
        );
    }

    int w = cfg.camera.width;
    int h = cfg.camera.height;
    if (wantPPM) {
        std::cout << "P3\n" << w << " " << h << "\n255\n";
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double u = (x + 0.5) / w;
            double v = (y + 0.5) / h;
            RayTracer::Ray ray = scene.getCamera().ray(u, v);

            Color finalColor(0, 0, 0);
            double closest_t = std::numeric_limits<double>::max();
            std::shared_ptr<RayTracer::IPrimitive> closestObject = nullptr;
            Math::Point3D hitPoint;
            Math::Vector3D normal;

            for (const auto &obj : scene.getObjects()) {
                double t;
                Math::Point3D pt;
                Math::Vector3D n;
                if (obj->intersect(ray, t, pt, n) && t < closest_t) {
                    closest_t = t;
                    closestObject = obj;
                    hitPoint = pt;
                    normal = n;
                }
            }

            if (closestObject) {
                // Start with ambient
                if (scene.getAmbient()) {
                    finalColor = scene.getAmbient()->illuminate(ray, *closestObject, hitPoint);
                }
                // Lighting
                for (const auto &light : scene.getLights()) {
                    if (auto *dirLight = dynamic_cast<RayTracer::DirectionalLight *>(light.get())) {
                        Math::Vector3D lightDir = dirLight->getDirection() * -1.0;
                        lightDir = lightDir / lightDir.length();

                        // Shadow ray
                        const double bias = 1e-4;
                        Math::Point3D shadowOrigin = hitPoint + normal * bias;
                        RayTracer::Ray shadowRay(shadowOrigin, lightDir);
                        bool shadowed = false;

                        for (const auto &obj : scene.getObjects()) {
                            if (obj != closestObject) {
                                double tTmp;
                                Math::Point3D tmpPt;
                                Math::Vector3D tmpN;
                                if (obj->intersect(shadowRay, tTmp, tmpPt, tmpN)) {
                                    shadowed = true;
                                    break;
                                }
                            }
                        }
                        if (!shadowed) {
                            double diff = std::max(0.0, normal.dot(lightDir));
                            Color lightColor = light->illuminate(ray, *closestObject, hitPoint);
                            finalColor.r = std::min(finalColor.r + static_cast<int>(lightColor.r * diff), 255);
                            finalColor.g = std::min(finalColor.g + static_cast<int>(lightColor.g * diff), 255);
                            finalColor.b = std::min(finalColor.b + static_cast<int>(lightColor.b * diff), 255);
                        }

                    } else if (auto *pLight = dynamic_cast<RayTracer::PointLight *>(light.get())) {
                        Math::Vector3D lightDir = pLight->getPosition() - hitPoint;
                        double dist = lightDir.length();
                        lightDir = lightDir / dist;

                        const double bias = 1e-4;
                        Math::Point3D shadowOrig = hitPoint + normal * bias;
                        RayTracer::Ray shadowRay(shadowOrig, lightDir);
                        bool inShadow = false;
                        for (const auto &obj : scene.getObjects()) {
                            if (obj != closestObject) {
                                double tTmp;
                                Math::Point3D tmpPt;
                                Math::Vector3D tmpN;
                                if (obj->intersect(shadowRay, tTmp, tmpPt, tmpN) && tTmp < dist) {
                                    inShadow = true;
                                    break;
                                }
                            }
                        }
                        if (!inShadow) {
                            double diff = std::max(0.0, normal.dot(lightDir));
                            Color c = light->illuminate(ray, *closestObject, hitPoint);
                            finalColor.r = std::min(finalColor.r + static_cast<int>(c.r * diff), 255);
                            finalColor.g = std::min(finalColor.g + static_cast<int>(c.g * diff), 255);
                            finalColor.b = std::min(finalColor.b + static_cast<int>(c.b * diff), 255);
                        }
                    }
                }
            }

            if (wantPPM) {
                std::cout << finalColor.toPPM() << "\n";
            } else {
                display.pushPixel(x, y, Display::Pixel(finalColor.r, finalColor.g, finalColor.b));
            }
        }
    }
    if (!wantPPM)
        display.notifyDone();
}

int main(int argc, char **argv)
{
    try {
        Main main;
        std::string file;
        bool isDebug, wantPPM = false;
        main.parseArguments(argc, argv, file, isDebug, wantPPM);

        auto cfg = Config::parseScene(file);

        if (isDebug) {
            main.debug_config(cfg);
            return 0;
        }

        if (wantPPM) {
            Display display(cfg.camera.width, cfg.camera.height);
            main.calculPPM(cfg, display, wantPPM);
        } else {
            Display display(cfg.camera.width, cfg.camera.height);
            display.init();
            std::thread worker(&Main::calculPPM, &main, cfg, std::ref(display), wantPPM);
            display.run();
            if (worker.joinable())
                worker.join();
        }

    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
