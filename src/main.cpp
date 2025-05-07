/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/
#include <thread>
#include <cmath>
#include <dlfcn.h>
#include "../include/Main.hpp"
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"
#include "../include/IMaterial.hpp"
#include "../include/IPrimitive.hpp"
#include "../include/Camera.hpp"
#include "../include/Scene.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/PointLight.hpp"
#include "../include/Color.hpp"

using RayTracer::IPrimitive;

std::unique_ptr<IPrimitive> loadPrimitive(const std::string &soName)
{
    void *handle = dlopen(("./plugins/" + soName).c_str(), RTLD_LAZY);
    if (!handle)
        throw RayTracerException("Cannot open plugin: " + std::string(dlerror()));

    using CreateFunc = std::unique_ptr<IPrimitive>(*)();
    CreateFunc create = reinterpret_cast<CreateFunc>(dlsym(handle, "create"));
    if (!create)
        throw RayTracerException("Cannot find create function: " + std::string(dlerror()));

    return create();
}

void Main::printHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE> [-d] [-w]\n";
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
    }

    file = argv[1];
    if (!is_valid_cfg(file)) {
        throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
    }
}

void Main::addObjectsToScene(RayTracer::Scene &scene, const Config::Scene &cfg)
{
    for (const auto &s : cfg.spheres) {
        auto obj = loadPrimitive("libsphere.so");
        obj->setPosition(s.center);
        obj->setRadius(s.radius);
        obj->setMaterial(std::make_shared<RayTracer::FlatColor>(s.color));
        scene.addObject(std::move(obj));
    }
    for (const auto &c : cfg.cylinders) {
        auto obj = loadPrimitive("libcylinder.so");
        obj->setPosition(c.base);
        obj->setRadius(c.radius);
        obj->setMaterial(std::make_shared<RayTracer::FlatColor>(c.color));
        scene.addObject(std::move(obj));
    }
    for (const auto &cone : cfg.cones) {
        auto obj = loadPrimitive("libcone.so");
        obj->setPosition(cone.apex);
        obj->setRadius(cone.radius);
        obj->setHeight(cone.height);
        obj->setMaterial(std::make_shared<RayTracer::FlatColor>(cone.color));
        scene.addObject(std::move(obj));
    }
    for (const auto &p : cfg.planes) {
        auto obj = loadPrimitive("libplane.so");
        obj->setAxis(p.axis);
        Math::Point3D pos;
        if (p.axis == 'X') pos.x = p.position;
        else if (p.axis == 'Y') pos.y = p.position;
        else pos.z = p.position;
        obj->setPosition(pos);
        obj->setMaterial(std::make_shared<RayTracer::FlatColor>(p.color));
        scene.addObject(std::move(obj));
    }
}

void Main::calculPPM(const Config::Scene &cfg, Display &display, bool wantPPM)
{
    RayTracer::Scene scene;

    // CAMERA
    float aspect = static_cast<float>(cfg.camera.width) / cfg.camera.height;
    float scale  = std::tan((cfg.camera.fieldOfView * 0.5f) * M_PI / 180.0f);
    Math::Vector3D bs{-2.0f * scale * aspect, 0.0f, 0.0f};
    Math::Vector3D ls{0.0f, -2.0f * scale, 0.0f};
    Math::Point3D origin{
        cfg.camera.position.x - bs.x * 0.5f,
        cfg.camera.position.y - ls.y * 0.5f,
        cfg.camera.position.z - 1.0f
    };

    scene.setCamera(RayTracer::Camera(cfg.camera.position, RayTracer::Rectangle3D(origin, bs, ls)));

    // LIGHTS
    scene.setAmbientLight(std::make_unique<RayTracer::AmbientLight>(static_cast<float>(cfg.ambient)));
    for (const auto &d : cfg.directionals)
        scene.addLight(std::make_unique<RayTracer::DirectionalLight>(d.direction, static_cast<float>(cfg.diffuse)));
    for (const auto &p : cfg.points)
        scene.addLight(std::make_unique<RayTracer::PointLight>(p.position, static_cast<float>(cfg.diffuse)));

    // OBJECTS (load dynamiquement)
    this->addObjectsToScene(scene, cfg);

    int w = cfg.camera.width;
    int h = cfg.camera.height;
    if (wantPPM)
        std::cout << "P3\n" << w << " " << h << "\n255\n";

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
                if (scene.getAmbient())
                    finalColor = scene.getAmbient()->illuminate(ray, *closestObject, hitPoint);

                for (const auto &light : scene.getLights()) {
                    Math::Vector3D lightDir;
                    double dist = 0;
                    if (auto *dir = dynamic_cast<RayTracer::DirectionalLight *>(light.get())) {
                        lightDir = dir->getDirection() * -1.0;
                    } else if (auto *pt = dynamic_cast<RayTracer::PointLight *>(light.get())) {
                        lightDir = pt->getPosition() - hitPoint;
                        dist = lightDir.length();
                        lightDir = lightDir / dist;
                    }

                    const double bias = 1e-4;
                    Math::Point3D shadowOrig = hitPoint + normal * bias;
                    RayTracer::Ray shadowRay(shadowOrig, lightDir);
                    bool inShadow = false;

                    for (const auto &obj : scene.getObjects()) {
                        if (obj != closestObject) {
                            double tTmp;
                            Math::Point3D tmpPt;
                            Math::Vector3D tmpN;
                            if (obj->intersect(shadowRay, tTmp, tmpPt, tmpN) &&
                                (dist == 0 || tTmp < dist)) {
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

            if (wantPPM)
                std::cout << finalColor.toPPM() << "\n";
            else
                display.pushPixel(x, y, Display::Pixel(finalColor.r, finalColor.g, finalColor.b));
        }
    }
    if (!wantPPM)
        display.notifyDone();
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

    std::cout << "CYLINDERS:\n";
    for (const auto &c : cfg.cylinders) {
        std::cout << "base = (" << c.base.x << ", " << c.base.y << ", " << c.base.z << ")"
                  << "  axe = (" << c.axis.x << ", " << c.axis.y << ", " << c.axis.z << ")"
                  << "  rayon = " << c.radius
                  << "  hauteur = " << c.height
                  << "  couleur = (" << c.color.r << ", " << c.color.g << ", " << c.color.b << ")\n";
    }

    std::cout << "CONES:\n";
    for (const auto &c : cfg.cones) {
        std::cout << "apex = (" << c.apex.x << ", " << c.apex.y << ", " << c.apex.z << ")"
                  << "  axe = (" << c.axis.x << ", " << c.axis.y << ", " << c.axis.z << ")"
                  << "  rayon = " << c.radius
                  << "  hauteur = " << c.height
                  << "  couleur = (" << c.color.r << ", " << c.color.g << ", " << c.color.b << ")\n";
    }

    std::cout << "TRIANGLES:\n";
    /*for (const auto &t : cfg.triangles) {
        std::cout << "a = (" << t.a.x << ", " << t.a.y << ", " << t.a.z << ")"
                  << "  b = (" << t.b.x << ", " << t.b.y << ", " << t.b.z << ")"
                  << "  c = (" << t.c.x << ", " << t.c.y << ", " << t.c.z << ")"
                  << "  couleur = (" << t.color.r << ", " << t.color.g << ", " << t.color.b << ")\n";
    }*/

    std::cout << "PLANES:\n";
    for (const auto &p : cfg.planes) {
        std::cout << "axe = '" << p.axis << "'"
                  << "  position = " << p.position
                  << "  couleur = (" << p.color.r << ", " << p.color.g << ", " << p.color.b << ")\n";
    }

    std::cout << "LIGHTS:\n";
    std::cout << "ambient = " << cfg.ambient << "  diffuse = " << cfg.diffuse << "\n";
}

int main(int argc, char **argv) {
    try {
        Main main;
        std::string file;
        bool isDebug = false, wantPPM = false;
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
