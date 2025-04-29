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

void Main::parseArguments(int argc, char **argv, std::string &file, bool &isPPM, bool &isDebug)
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
    isPPM = (file.substr(file.find_last_of('.') + 1) == "ppm");
    if (!isPPM && !is_valid_cfg(file)) {
        throw RayTracerException("Error: SCENE_FILE must have .cfg extension");
    }
}

void Main::ppm(const std::string &file)
{
    Display display;
    display.parseFile(file);
    std::cout << "PPM size: " << display.getWidth() << " × " << display.getHeight() << std::endl;
    display.init();
    display.run();
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

void Main::calculPPM(const Config::Scene &cfg)
{
    RayTracer::Scene scene;

    float aspect = static_cast<float>(cfg.camera.width) /  cfg.camera.height;
    float scale  = std::tan((cfg.camera.fieldOfView * 0.5f) * M_PI / 180.0f);
    Math::Vector3D bs{2.0f * scale * aspect, 0.0f, 0.0f};
    Math::Vector3D ls{0.0f, 2.0f * scale, 0.0f};
    Math::Point3D origin{
        cfg.camera.position.x - bs.x * 0.5f,
        cfg.camera.position.y - ls.y * 0.5f,
        cfg.camera.position.z - 1.0f
    };
    // Camera setup
    scene.setCamera(
        RayTracer::Camera(
            cfg.camera.position,
            RayTracer::Rectangle3D(origin, bs, ls)
        )
    );

    // Lights setup
    scene.setAmbientLight(
        std::make_unique<RayTracer::AmbientLight>(
            static_cast<float>(cfg.ambient)
        )
    );
    for (const auto &d : cfg.directionals) {
        scene.addLight(
            std::make_unique<RayTracer::DirectionalLight>(
                d.direction,
                static_cast<float>(cfg.diffuse)
            )
        );
    }

    // Primitives setup
    for (const auto &s : cfg.spheres) {
        scene.addObject(
            std::make_shared<RayTracer::Sphere>(
                s.center,
                s.radius,
                std::make_shared<RayTracer::FlatColor>(s.color)
            )
        );
    }

    // Planes setup
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

    // PPM header
    int w = cfg.camera.width;
    int h = cfg.camera.height;
    std::cout << "P3\n"
              << w << " " << h << "\n"
              << "255\n";

    // Raytrace loop
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double u = (x + 0.5) / w;
            double v = (y + 0.5) / h;
            RayTracer::Ray ray  = scene.getCamera().ray(u, v);
            Color pixel{0, 0, 0};

            for (const auto &obj : scene.getObjects()) {
                if (obj->hits(ray)) {
                    if (scene.getAmbient()) {
                        pixel = scene.getAmbient()->illuminate(ray, *obj, Math::Point3D());
                    }
                    for (const auto &lt : scene.getLights()) {
                        auto c = lt->illuminate(ray, *obj, Math::Point3D());
                        pixel.r = std::min(pixel.r + c.r, 255);
                        pixel.g = std::min(pixel.g + c.g, 255);
                        pixel.b = std::min(pixel.b + c.b, 255);
                    }
                    break;
                }
            }

            std::cout << pixel.toPPM() << "\n";
        }
    }
}

int main(int argc, char **argv)
{
    try {
        Main main;
        std::string file;
        bool isPPM, isDebug = false;
        main.parseArguments(argc, argv, file, isPPM, isDebug);
        
        if (isPPM) {
            main.ppm(file);
            return 0;
        }

        auto cfg = Config::parseScene(file);

        if (isDebug) {
            main.debug_config(cfg);
            return 0;
        }

        main.calculPPM(cfg);

    } catch (const RayTracerException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
