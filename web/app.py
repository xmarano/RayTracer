import os
import subprocess
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__, static_folder="static")

CFG_FILE = "web.cfg"
PPM_FILE = "render.ppm"
PNG_FILE = os.path.join("static", "render.png")

@app.route("/", methods=["GET"])
def index():
    return render_template("index.html", img_src=url_for('static', filename='render.png'))

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

    # Sphere 1
    s1x  = getp("sphere1_x", 4)
    s1y  = getp("sphere1_y", 3.5)
    s1z  = getp("sphere1_z", 1)
    s1r  = getp("sphere1_radius", 1)
    s1cr = getp("sphere1_color_r", 200)
    s1cg = getp("sphere1_color_g", 100)
    s1cb = getp("sphere1_color_b", 0)

    # Sphere 2
    s2x  = getp("sphere2_x", 3)
    s2y  = getp("sphere2_y", 1)
    s2z  = getp("sphere2_z", 0)
    s2r  = getp("sphere2_radius", 1.5)
    s2cr = getp("sphere2_color_r", 0)
    s2cg = getp("sphere2_color_g", 100)
    s2cb = getp("sphere2_color_b", 200)

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
        f.write(f"        {{ x = {s1x}; y = {s1y}; z = {s1z}; r = {s1r}; color = {{ r = {s1cr}; g = {s1cg}; b = {s1cb}; }}; }},\n")
        f.write(f"        {{ x = {s2x}; y = {s2y}; z = {s2z}; r = {s2r}; color = {{ r = {s2cr}; g = {s2cg}; b = {s2cb}; }}; }}\n")
        f.write("    );\n")
        f.write("    cylinders = ();\n")
        f.write("    cones = ();\n")
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
    with open(PPM_FILE, "wb") as ppm_out:
        subprocess.run(["./raytracer_web", CFG_FILE, "-w"], check=True, stdout=ppm_out)

    subprocess.run(["magick", PPM_FILE, PNG_FILE], check=True)

    return redirect(url_for("index"))

if __name__ == "__main__":
    os.makedirs("static", exist_ok=True)
    app.run(host="0.0.0.0", port=9999, debug=True)
