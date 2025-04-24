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
    try {
    // Camera
        // resolution
        cfg.lookupValue("camera.resolution.width", scene.camera.width);
        cfg.lookupValue("camera.resolution.height", scene.camera.height);
        // position
        cfg.lookupValue("camera.position.x", scene.camera.position.x);
        cfg.lookupValue("camera.position.y", scene.camera.position.y);
        cfg.lookupValue("camera.position.z", scene.camera.position.z);
        // rotation
        cfg.lookupValue("camera.rotation.x", scene.camera.rotation.x);
        cfg.lookupValue("camera.rotation.y", scene.camera.rotation.y);
        cfg.lookupValue("camera.rotation.z", scene.camera.rotation.z);
        // fieldOfView
        cfg.lookupValue("camera.fieldOfView", scene.camera.fieldOfView);

    // Primitives
        // Spheres
        const libconfig::Setting &spheres = cfg.lookup("primitives.spheres");
        for (int i = 0; i < spheres.getLength(); ++i) {
            const libconfig::Setting &config_sphere = spheres[i];
            Config::Sphere s;

            // center
            s.center.x = config_sphere.lookup("x");
            s.center.y = config_sphere.lookup("y");
            s.center.z = config_sphere.lookup("z");
            // radius
            s.radius = config_sphere.lookup("r");
            // color
            const libconfig::Setting &config_color = config_sphere.lookup("color");
            s.color = Color(
                config_color.lookup("r"),
                config_color.lookup("g"),
                config_color.lookup("b")
            );

            scene.spheres.push_back(s);
        }

        // Planes
        const libconfig::Setting &planes = cfg.lookup("primitives.planes");
        for (int i = 0; i < planes.getLength(); ++i) {
            const libconfig::Setting &config_plane = planes[i];
            Config::Plane p;

            // axis
            std::string ax;
            config_plane.lookupValue("axis", ax);
            p.axis = ax[0];
            // position
            p.position = config_plane.lookup("position");
            // color
            const libconfig::Setting &config_color = config_plane.lookup("color");
            p.color = Color(
                config_color.lookup("r"),
                config_color.lookup("g"),
                config_color.lookup("b")
            );

            scene.planes.push_back(p);
        }

    // Lights
        // ambient
        cfg.lookupValue("lights.ambient", scene.ambient);
        // diffuse
        cfg.lookupValue("lights.diffuse", scene.diffuse);
        // point
        const libconfig::Setting &points = cfg.lookup("lights.point");
        for (int i = 0; i < points.getLength(); ++i) {
            const libconfig::Setting &config_point = points[i];
            Config::Point p;

            // position
            p.position.x = config_point.lookup("x");
            p.position.y = config_point.lookup("y");
            p.position.z = config_point.lookup("z");

            scene.points.push_back(p);
        }

        // // directional
        // const libconfig::Setting &directionals = cfg.lookup("lights.directional");
        // for (int i = 0; i < directionals.getLength(); ++i) {
        //     const libconfig::Setting &config_directional = directionals[i];
        //     Config::Directional d;
    
        //     // direction
        //     d.direction.x = config_directional.lookup("x");
        //     d.direction.y = config_directional.lookup("y");
        //     d.direction.z = config_directional.lookup("z");
        //     // color
        //     const libconfig::Setting &config_color = config_directional.lookup("color");
        //     d.color = Color(
        //         config_color.lookup("r"),
        //         config_color.lookup("g"),
        //         config_color.lookup("b")
        //     );
    
        //     scene.directionals.push_back(d);
        // }
    } catch (const libconfig::SettingNotFoundException &nf) {
        // si y a pas faut voir ce qu'on fait
    }

    return scene;
}
