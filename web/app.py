import os
import subprocess
from time import time
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__, static_folder="static")

CFG_FILE = "web.cfg"
PPM_FILE = "render.ppm"
PNG_FILE = os.path.join("static", "render.png")

@app.route("/", methods=["GET"])
def index():
    version = int(time())
    return render_template("index.html", img_src=url_for('static', filename='render.png'), version=version)

@app.route("/set_configuration", methods=["POST"])
def set_configuration():
    def getp(name, default):
        v = request.form.get(name)
        return v if v not in (None, "") else str(default)

    # Camera
    w   = getp("camera_resolution_width", 1280)
    h   = getp("camera_resolution_height", 720)
    px  = getp("camera_position_x", 0)
    py  = getp("camera_position_y", 5)
    pz  = getp("camera_position_z", 15)
    rx  = getp("camera_rotation_x", 0)
    ry  = getp("camera_rotation_y", 0)
    rz  = getp("camera_rotation_z", 0)
    fov = getp("camera_fov", 50)

    # Sphere
    sx  = getp("sphere_x", 4)
    sy  = getp("sphere_y", 3.5)
    sz  = getp("sphere_z", 1)
    sr  = getp("sphere_radius", 1)
    scr = getp("sphere_color_r", 200)
    scg = getp("sphere_color_g", 100)
    scb = getp("sphere_color_b", 0)

    # Cylinder
    cyl_base_x = getp("cyl_base_x", -5)
    cyl_base_y = getp("cyl_base_y", 0)
    cyl_base_z = getp("cyl_base_z", 0)
    cyl_axis_x = getp("cyl_axis_x", 10)
    cyl_axis_y = getp("cyl_axis_y", 5)
    cyl_axis_z = getp("cyl_axis_z", 0)
    cyl_radius = getp("cyl_radius", 1)
    cyl_height = getp("cyl_height", 2)
    cyl_r = getp("cyl_color_r", 255)
    cyl_g = getp("cyl_color_g", 0)
    cyl_b = getp("cyl_color_b", 0)

    # Cone
    cone_apex_x = getp("cone_apex_x", 5)
    cone_apex_y = getp("cone_apex_y", 0)
    cone_apex_z = getp("cone_apex_z", 3)
    cone_axis_x = getp("cone_axis_x", 10)
    cone_axis_y = getp("cone_axis_y", 10)
    cone_axis_z = getp("cone_axis_z", 0)
    cone_radius = getp("cone_radius", 1)
    cone_height = getp("cone_height", 4)
    cone_r = getp("cone_color_r", 0)
    cone_g = getp("cone_color_g", 255)
    cone_b = getp("cone_color_b", 255)

    # Triangle
    tri_ax = getp("tri_ax", -2)
    tri_ay = getp("tri_ay", 2)
    tri_az = getp("tri_az", 2)
    tri_bx = getp("tri_bx", 4)
    tri_by = getp("tri_by", 3)
    tri_bz = getp("tri_bz", 0)
    tri_cx = getp("tri_cx", 1)
    tri_cy = getp("tri_cy", 4)
    tri_cz = getp("tri_cz", 0)
    tri_r = getp("tri_color_r", 255)
    tri_g = getp("tri_color_g", 0)
    tri_b = getp("tri_color_b", 0)

    # Plane 1
    p1a  = getp("plane1_axis", "Y")
    p1p  = getp("plane1_position", -1)
    p1cr = getp("plane1_color_r", 230)
    p1cg = getp("plane1_color_g", 230)
    p1cb = getp("plane1_color_b", 230)

    # Plane 2
    p2a  = getp("plane2_axis", "X")
    p2p  = getp("plane2_position", -10)
    p2cr = getp("plane2_color_r", 150)
    p2cg = getp("plane2_color_g", 150)
    p2cb = getp("plane2_color_b", 150)

    # Lights
    ambient = getp("light_ambient", 0.3)
    diffuse = getp("light_diffuse", 0.7)

    # Point light
    plx  = getp("light_point_x", 2)
    ply  = getp("light_point_y", 8)
    plz  = getp("light_point_z", 5)
    pli  = getp("light_point_intensity", 0.5)
    plcr = getp("light_point_color_r", 255)
    plcg = getp("light_point_color_g", 240)
    plcb = getp("light_point_color_b", 210)

    # Directional
    dx   = getp("light_directional_x", 0)
    dy   = getp("light_directional_y", -1)
    dz   = getp("light_directional_z", -0.5)

    # Write web.cfg
    with open(CFG_FILE, "w") as f:
        f.write("camera : {\n")
        f.write(f"    resolution = {{ width = {w}; height = {h}; }};\n")
        f.write(f"    position   = {{ x = {px}; y = {py}; z = {pz}; }};\n")
        f.write(f"    rotation   = {{ x = {rx}; y = {ry}; z = {rz}; }};\n")
        f.write(f"    fieldOfView = {fov};\n")
        f.write("};\n\n")

        f.write("primitives : {\n")
        f.write("    spheres = (\n")
        f.write(f"        {{ x = {sx}; y = {sy}; z = {sz}; r = {sr}; color = {{ r = {scr}; g = {scg}; b = {scb}; }}; }}\n")
        f.write("    );\n")
        f.write("    cylinders = (\n")
        f.write(f"        {{ base = {{ x = {cyl_base_x}; y = {cyl_base_y}; z = {cyl_base_z}; }}; axis = {{ x = {cyl_axis_x}; y = {cyl_axis_y}; z = {cyl_axis_z}; }}; radius = {cyl_radius}; height = {cyl_height}; color = {{ r = {cyl_r}; g = {cyl_g}; b = {cyl_b}; }}; }}\n")
        f.write("    );\n")
        f.write("    cones = (\n")
        f.write(f"        {{ apex = {{ x = {cone_apex_x}; y = {cone_apex_y}; z = {cone_apex_z}; }}; axis = {{ x = {cone_axis_x}; y = {cone_axis_y}; z = {cone_axis_z}; }}; radius = {cone_radius}; height = {cone_height}; color = {{ r = {cone_r}; g = {cone_g}; b = {cone_b}; }}; }}\n")
        f.write("    );\n")
        f.write("    triangles = (\n")
        f.write(f"        {{ a = {{ x = {tri_ax}; y = {tri_ay}; z = {tri_az}; }}; b = {{ x = {tri_bx}; y = {tri_by}; z = {tri_bz}; }}; c = {{ x = {tri_cx}; y = {tri_cy}; z = {tri_cz}; }}; color = {{ r = {tri_r}; g = {tri_g}; b = {tri_b}; }}; }}\n")
        f.write("    );\n")
        f.write("    planes = (\n")
        f.write(f"        {{ axis = \"{p1a}\"; position = {p1p}; color = {{ r = {p1cr}; g = {p1cg}; b = {p1cb}; }}; }},\n")
        f.write(f"        {{ axis = \"{p2a}\"; position = {p2p}; color = {{ r = {p2cr}; g = {p2cg}; b = {p2cb}; }}; }}\n")
        f.write("    );\n")
        f.write("};\n\n")

        f.write("lights : {\n")
        f.write(f"    ambient = {ambient};\n")
        f.write(f"    diffuse = {diffuse};\n")
        f.write("    point = (\n")
        f.write(f"        {{ x = {plx}; y = {ply}; z = {plz}; intensity = {pli}; color = {{ r = {plcr}; g = {plcg}; b = {plcb}; }}; }}\n")
        f.write("    );\n")
        f.write(f"    directional = ({{ x = {dx}; y = {dy}; z = {dz}; }});\n")
        f.write("};\n")

    # Run raytracer
    raytracer_executable = ""
    if os.uname().sysname == "Darwin":
        raytracer_executable = "./raytracer_web_darwin"
    else:
        raytracer_executable = "./raytracer_web_linux"
    with open(PPM_FILE, "wb") as ppm_out:
        subprocess.run([raytracer_executable, CFG_FILE, "-w"], check=True, stdout=ppm_out)

    subprocess.run(["convert", PPM_FILE, PNG_FILE], check=True)

    return redirect(url_for("index"))

if __name__ == "__main__":
    os.makedirs("static", exist_ok=True)
    app.run(host="0.0.0.0", port=9999, debug=True)
