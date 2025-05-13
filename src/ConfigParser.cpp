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
    Scene scene;
    cfg.setAutoConvert(true);

    try {
        cfg.readFile(file.c_str());
    } catch (const libconfig::FileIOException &) {
        throw RayTracerException("Error: Unable to read the configuration file");
    } catch (const libconfig::ConfigException &) {
        throw RayTracerException("Error: Invalid configuration file format");
    }

    cfg.lookupValue("camera.resolution.width",  scene.camera.width);
    cfg.lookupValue("camera.resolution.height", scene.camera.height);
    cfg.lookupValue("camera.position.x",      scene.camera.position.x);
    cfg.lookupValue("camera.position.y",      scene.camera.position.y);
    cfg.lookupValue("camera.position.z",      scene.camera.position.z);
    cfg.lookupValue("camera.rotation.x",      scene.camera.rotation.x);
    cfg.lookupValue("camera.rotation.y",      scene.camera.rotation.y);
    cfg.lookupValue("camera.rotation.z",      scene.camera.rotation.z);
    cfg.lookupValue("camera.fieldOfView",     scene.camera.fieldOfView);

    try {
        const auto &spheres = cfg.lookup("primitives.spheres");
        for (int i = 0; i < spheres.getLength(); ++i) {
            const auto &s = spheres[i];
            Config::Sphere obj;
            obj.center.x = s.lookup("x");
            obj.center.y = s.lookup("y");
            obj.center.z = s.lookup("z");
            obj.radius   = s.lookup("r");
            const auto &col = s.lookup("color");
            obj.color = Color(
                col.lookup("r"),
                col.lookup("g"),
                col.lookup("b")
            );
            scene.spheres.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &cylinders = cfg.lookup("primitives.cylinders");
        for (int i = 0; i < cylinders.getLength(); ++i) {
            const auto &cset = cylinders[i];
            Config::Cylinder obj;
            const auto &base = cset.lookup("base");
            obj.base.x = base.lookup("x");
            obj.base.y = base.lookup("y");
            obj.base.z = base.lookup("z");
            const auto &axis = cset.lookup("axis");
            obj.axis.x = axis.lookup("x");
            obj.axis.y = axis.lookup("y");
            obj.axis.z = axis.lookup("z");
            obj.radius = cset.lookup("radius");
            obj.height = cset.lookup("height");
            const auto &col = cset.lookup("color");
            obj.color = Color(
                col.lookup("r"),
                col.lookup("g"),
                col.lookup("b")
            );
            scene.cylinders.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &cones = cfg.lookup("primitives.cones");
        for (int i = 0; i < cones.getLength(); ++i) {
            const auto &cset = cones[i];
            Config::Cone obj;
            const auto &apex = cset.lookup("apex");
            obj.apex.x = apex.lookup("x");
            obj.apex.y = apex.lookup("y");
            obj.apex.z = apex.lookup("z");
            const auto &axis = cset.lookup("axis");
            obj.axis.x = axis.lookup("x");
            obj.axis.y = axis.lookup("y");
            obj.axis.z = axis.lookup("z");
            obj.radius = cset.lookup("radius");
            obj.height = cset.lookup("height");
            const auto &col = cset.lookup("color");
            obj.color = Color(
                col.lookup("r"),
                col.lookup("g"),
                col.lookup("b")
            );
            scene.cones.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &triangles = cfg.lookup("primitives.triangles");
        for (int i = 0; i < triangles.getLength(); ++i) {
            const auto &tset = triangles[i];
            Config::Triangle obj;
            const auto &a = tset.lookup("a");
            obj.a.x = a.lookup("x"); obj.a.y = a.lookup("y"); obj.a.z = a.lookup("z");
            const auto &b = tset.lookup("b");
            obj.b.x = b.lookup("x"); obj.b.y = b.lookup("y"); obj.b.z = b.lookup("z");
            const auto &_c = tset.lookup("c");
            obj.c.x = _c.lookup("x"); obj.c.y = _c.lookup("y"); obj.c.z = _c.lookup("z");
            const auto &col = tset.lookup("color");
            obj.color = Color(
                col.lookup("r"),
                col.lookup("g"),
                col.lookup("b")
            );
            scene.triangles.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &planes = cfg.lookup("primitives.planes");
        for (int i = 0; i < planes.getLength(); ++i) {
            const auto &pset = planes[i];
            Config::Plane obj;
            std::string axisStr;
            pset.lookupValue("axis", axisStr);
            obj.axis = axisStr[0];
            obj.position = pset.lookup("position");
            const auto &col = pset.lookup("color");
            obj.color = Color(
                col.lookup("r"),
                col.lookup("g"),
                col.lookup("b")
            );
            scene.planes.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &objs = cfg.lookup("primitives.objs");
        for (int i = 0; i < objs.getLength(); ++i) {
            const auto &oset = objs[i];
            Config::ObjFile obj;
            oset.lookupValue("path", obj.path);
            if (oset.exists("translation")) {
                const auto &t = oset.lookup("translation");
                obj.translation.x = t.lookup("x");
                obj.translation.y = t.lookup("y");
                obj.translation.z = t.lookup("z");
            }
            if (oset.exists("rotation")) {
                const auto &r = oset.lookup("rotation");
                obj.rotation.x = r.lookup("x");
                obj.rotation.y = r.lookup("y");
                obj.rotation.z = r.lookup("z");
            }
            if (oset.exists("color")) {
                const auto &col = oset.lookup("color");
                obj.color = Color(
                    col.lookup("r"),
                    col.lookup("g"),
                    col.lookup("b")
                );
            }
            scene.objs.push_back(obj);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try { cfg.lookupValue("lights.ambient", scene.ambient); } catch(...) {}
    try { cfg.lookupValue("lights.diffuse", scene.diffuse); } catch(...) {}

    try {
        const auto &points = cfg.lookup("lights.point");
        for (int i = 0; i < points.getLength(); ++i) {
            Config::Point p;
            const auto &ps = points[i];
            p.position.x = ps.lookup("x");
            p.position.y = ps.lookup("y");
            p.position.z = ps.lookup("z");
            scene.points.push_back(p);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    try {
        const auto &dirs = cfg.lookup("lights.directional");
        for (int i = 0; i < dirs.getLength(); ++i) {
            Config::Directional d;
            const auto &ds = dirs[i];
            d.direction.x = ds.lookup("x");
            d.direction.y = ds.lookup("y");
            d.direction.z = ds.lookup("z");
            scene.directionals.push_back(d);
        }
    } catch (const libconfig::SettingNotFoundException &) {}

    return scene;
}
