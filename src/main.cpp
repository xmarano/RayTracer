/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Main.cpp
*/
#include "../include/Main.hpp"
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"
#include "../include/Display.hpp"
#include "../include/ConfigParser.hpp"
#include "../include/IMaterial.hpp"
#include "../include/AmbientLight.hpp"
#include "../include/DirectionalLight.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plane.hpp"
#include "../include/Camera.hpp"
#include "../include/Scene.hpp"

void Main::printHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    std::cout << "  SCENE_FILE: scene configuration\n";
}

void Main::parseArguments(int argc, char **argv, std::string &file, bool &isDebug)
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

    if (argc != 2) {
        throw RayTracerException("USAGE: ./raytracer <SCENE_FILE>");
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
    std::cout << "position = (" << cfg.camera.position.x << ", "   << cfg.camera.position.y << ", "   << cfg.camera.position.z << ")\n";
    std::cout << "rotation = (" << cfg.camera.rotation.x << ", "   << cfg.camera.rotation.y << ", "   << cfg.camera.rotation.z << ")\n";
    std::cout << "fieldOfView = " << cfg.camera.fieldOfView << std::endl << std::endl;

    std::cout << "SPHERES:\n";
    for (const auto &s : cfg.spheres) {
        std::cout << "centre = (" << s.center.x << ", "    << s.center.y << ", "    << s.center.z << ")"
                  << "  rayon = "    << s.radius
                  << "  couleur = (" << s.color.r << ", "    << s.color.g << ", "    << s.color.b << ")\n";
    }

    std::cout << "PLANES:\n";
    for (const auto &p : cfg.planes) {
        std::cout << "axe = '" << p.axis << "'"
                  << "  position = "  << p.position
                  << "  couleur = (" << p.color.r << ", "    << p.color.g << ", "    << p.color.b << ")\n";
    }

    std::cout << "LIGHTS:\n";
    std::cout << "ambient = " << cfg.ambient
              << "  diffuse = " << cfg.diffuse << "\n";
}

void Main::calculPPM(const Config::Scene &cfg, Display &display)
{
    RayTracer::Scene scene;
    float aspect = float(cfg.camera.width) / cfg.camera.height;
    float scale  = std::tan((cfg.camera.fieldOfView * 0.5f) * M_PI / 180.f);
    Math::Vector3D bs{2 * scale * aspect, 0, 0}, ls{0, 2 * scale, 0};
    Math::Point3D origin{
        cfg.camera.position.x - bs.x / 2,
        cfg.camera.position.y - ls.y / 2,
        cfg.camera.position.z - 1
    };

    scene.setCamera(
        RayTracer::Camera(
            cfg.camera.position,
            RayTracer::Rectangle3D(origin, bs, ls)
        )
    );

    scene.setAmbientLight(
        std::make_unique<RayTracer::AmbientLight>(
            cfg.ambient
        )
    );

    for (auto &d : cfg.directionals) {
        scene.addLight(
            std::make_unique<RayTracer::DirectionalLight>(
                d.direction,
                cfg.diffuse
            )
        );
    }

    for (auto &s : cfg.spheres) {
        scene.addObject(
            std::make_shared<RayTracer::Sphere>(
                s.center,
                s.radius,
                std::make_shared<RayTracer::FlatColor>(s.color)
            )
        );
    }

    for (auto &p : cfg.planes) {
        Math::Vector3D normal{0, 0, 0};
        if (p.axis == 'X') normal.x = 1;
        else if (p.axis == 'Y') normal.y = 1;
        else normal.z = 1;

        Math::Point3D pt{0, 0, 0};
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

    // render -> push display
    int w = cfg.camera.width, h = cfg.camera.height;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            double u = (x + 0.5) / w, v = (y + 0.5) / h;
            RayTracer::Ray ray = scene.getCamera().ray(u, v);
            Color pixel{0, 0, 0};
            for (auto &obj : scene.getObjects()) {
                if (obj->hits(ray)) {
                    if (scene.getAmbient())
                        pixel = scene.getAmbient()->illuminate(ray, *obj, {});
                    for (auto &lt : scene.getLights()) {
                        auto c = lt->illuminate(ray, *obj, {});
                        pixel.r = std::min(pixel.r + c.r, 255);
                        pixel.g = std::min(pixel.g + c.g, 255);
                        pixel.b = std::min(pixel.b + c.b, 255);
                    }
                    break;
                }
            }
            display.pushPixel(x, y, Display::Pixel(pixel.r, pixel.g, pixel.b));
        }
    }

    display.notifyDone();
}

int main(int argc, char **argv)
{
    try {
        Main main;
        std::string file;
        bool isDebug = false;
        main.parseArguments(argc, argv, file, isDebug);

        auto cfg = Config::parseScene(file);

        if (isDebug) {
            main.debug_config(cfg);
            return 0;
        }

        Display display(cfg.camera.width, cfg.camera.height);
        display.init();

        std::thread calculThread(&Main::calculPPM, &main, cfg, std::ref(display));
        display.run();

        if (calculThread.joinable())
            calculThread.join();
    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
