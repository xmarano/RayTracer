/*
** EPITECH PROJECT, 2025
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

        // Cylinders
        const libconfig::Setting &cylinders = cfg.lookup("primitives.cylinders");
        for (int i = 0; i < cylinders.getLength(); ++i) {
            const libconfig::Setting &config_cylinder = cylinders[i];
            Config::Cylinder c;

            // base
            const libconfig::Setting &base = config_cylinder.lookup("base");
            c.base.x = base.lookup("x");
            c.base.y = base.lookup("y");
            c.base.z = base.lookup("z");
            // axis
            const libconfig::Setting &axis = config_cylinder.lookup("axis");
            c.axis.x = axis.lookup("x");
            c.axis.y = axis.lookup("y");
            c.axis.z = axis.lookup("z");

            // radius
            c.radius = config_cylinder.lookup("radius");
            // height
            c.height = config_cylinder.lookup("height");
            // color
            const libconfig::Setting &config_color = config_cylinder.lookup("color");
            c.color = Color(
                config_color.lookup("r"),
                config_color.lookup("g"),
                config_color.lookup("b")
            );
            scene.cylinders.push_back(c);
        }

        // Cones
        const libconfig::Setting &cones = cfg.lookup("primitives.cones");
        for (int i = 0; i < cones.getLength(); ++i) {
            const libconfig::Setting &config_cone = cones[i];
            Config::Cone c;

            // apex
            const libconfig::Setting &apex = config_cone.lookup("apex");
            c.apex.x = apex.lookup("x");
            c.apex.y = apex.lookup("y");
            c.apex.z = apex.lookup("z");
            // axis
            const libconfig::Setting &axis = config_cone.lookup("axis");
            c.axis.x = axis.lookup("x");
            c.axis.y = axis.lookup("y");
            c.axis.z = axis.lookup("z");

            // radius
            c.radius = config_cone.lookup("radius");
            // height
            c.height = config_cone.lookup("height");
            // color
            const libconfig::Setting &config_color = config_cone.lookup("color");
            c.color = Color(
                config_color.lookup("r"),
                config_color.lookup("g"),
                config_color.lookup("b")
            );
            scene.cones.push_back(c);
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

        // directional
        const libconfig::Setting &directionals = cfg.lookup("lights.directional");
        for (int i = 0; i < directionals.getLength(); ++i) {
            const libconfig::Setting &config_directional = directionals[i];
            Config::Directional d;
    
            // direction
            d.direction.x = config_directional.lookup("x");
            d.direction.y = config_directional.lookup("y");
            d.direction.z = config_directional.lookup("z");
    
            scene.directionals.push_back(d);
        }
    } catch (const libconfig::SettingNotFoundException &nf) {
        // si y a pas faut voir ce qu'on fait
    }

    return scene;
}
