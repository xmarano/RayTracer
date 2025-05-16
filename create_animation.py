import os, sys, math
from tqdm import tqdm
from time import sleep

def congif_sphere(x1, y1, z1, x2, y2, z2):
    return f"""
camera : {{
    resolution = {{ width = 1280; height = 720; }};
    position   = {{ x = 0; y = 5; z = 15; }};
    rotation   = {{ x = 0; y = 0; z = 0; }};
    fieldOfView = 50.0;
}};

primitives : {{
    spheres = (
        {{ x = {x1:.1f}; y = {y1:.1f}; z = {z1:.1f}; r = 1.5; color = {{ r = 0; g = 100; b = 200; }}; }},
        {{ x = {x2:.1f}; y = {y2:.1f}; z = {z2:.1f}; r = 1.5; color = {{ r = 200; g =   0; b =   0; }}; }}
    );
    cylinders = ();
    cones = ();
    triangles = ();
    planes = (
        {{ axis = "Y"; position = -1; color = {{ r = 150; g = 150; b = 150; }}; }},
    );
}};

lights : {{
    ambient = 0.3;
    diffuse = 0.7;
    point = (
        {{ x = 2; y = 8; z = 5; intensity = 0.5; color = {{ r = 255; g = 244; b = 214; }}; }}
    );
    directional = (
        {{ x = -0.5; y = -1; z = -0.5; }}
    );
}};
"""

def create_config_files_spheres(img):
    cx, cy, cz =  0.0, 1.5, -6.5
    R = 6.0

    for i in range(img):
        theta = 2 * math.pi * i / img
        x1 = cx + R * math.cos(theta)
        z1 = cz + R * math.sin(theta)
        x2 = cx + R * math.cos(theta + math.pi)
        z2 = cz + R * math.sin(theta + math.pi)

        cfg = congif_sphere(x1, cy, z1, x2, cy, z2)
        with open(f"scenes/config_animation/{i:02}.cfg", "w") as f:
            f.write(cfg)
    print("Config files created for dual orbit")

def congif_cones(ay1, az1, ay2, az2):
    return f"""
camera : {{
    resolution = {{ width = 1280; height = 720; }};
    position   = {{ x = 0; y = 5; z = 15; }};
    rotation   = {{ x = 0; y = 0; z = 0; }};
    fieldOfView = 50.0;
}};

primitives : {{
    spheres = (
        {{ x = 0; y = 3.5; z = 1; r = 1; color = {{ r = 200; g = 100; b = 0; }}; }}
    );
    cones = (
        {{ apex = {{ x = 2; y = {ay1:.2f}; z = {az1:.2f}; }}; axis = {{ x = -45; y = -6; z = 0; }}; radius = 1.0;  height = 4.0; color = {{ r = 0; g = 255; b = 255; }}; }},
        {{ apex = {{ x = -2; y = {ay2:.2f}; z = {az2:.2f}; }}; axis = {{ x = 45; y = 3; z = 0; }}; radius = 1.0;  height = 4.0; color = {{ r = 255; g = 0; b = 255; }}; }}
    );
    cylinders = ();
    triangles = ();
    planes = (
        {{ axis = "Y"; position = -1; color = {{ r = 150; g = 150; b = 150; }}; }}
    );
}};

lights : {{
    ambient = 0.3;
    diffuse = 0.7;
    point = (
        {{ x = 2; y = 8; z = 5; intensity = 0.5; color = {{ r = 255; g = 244; b = 214; }}; }}
    );
    directional = (
        {{ x = -0.5; y = -1; z = -0.5; }}
    );
}};
"""

def create_config_files_cones(img):
    cy, cz = 3.5, 1.0
    Ry, Rz = 2.0, 1.5

    for i in range(img):
        theta = 2 * math.pi * i / img

        ay1 = cy + Ry * math.sin(theta)
        az1 = cz + Rz * math.cos(theta)

        ay2 = cy + Ry * math.sin(theta + math.pi)
        az2 = cz + Rz * math.cos(theta + math.pi)

        cfg = congif_cones(ay1, az1, ay2, az2)
        with open(f"scenes/config_animation/{i:02}.cfg", "w") as f:
            f.write(cfg)

    print("Config files created for dual cone orbit")

def create_config_files_cylinders(img):
    cx, cy = 4, 3.5
    R = 3.5

    for i in range(img):
        theta = 2 * math.pi * i / img
        cylinders = []

        x = cx + R * math.cos(theta)
        z = cy + R * math.sin(theta)
        y = 6

        cylinders.append(
            f'{{ base = {{ x = {x:.2f}; y = {y}; z = {z:.2f}; }}; axis = {{ x = 0; y = -0.3; z = 0; }}; radius = 0.5; height = 5; color = {{ r = 255; g = 0; b = 0; }};}}'
        )

        cfg = config_cylinders(cylinders)
        with open(f"scenes/config_animation/{i:02}.cfg", "w") as f:
            f.write(cfg)

    print("Config files created for rotating cylinder around the circle")

def config_cylinders(cylinders):
    return f"""
camera : {{
    resolution = {{ width = 1280; height = 720; }};
    position   = {{ x = 0; y = 5; z = 15; }};
    rotation   = {{ x = 0; y = 0; z = 0; }};
    fieldOfView = 50.0;
}};

primitives : {{
    spheres = (
        {{ x = 4; y = 3.5; z = 1; r = 1; color = {{ r = 50; g = 50; b = 150; }}; }}
    );
    cylinders = (
        {",".join(cylinders)}
    );
    cones = ();
    triangles = ();
    planes = (
        {{ axis = "Y"; position = -1; color = {{ r = 150; g = 150; b = 150; }}; }}
    );
}};

lights : {{
    ambient = 0.3;
    diffuse = 0.7;
    point = (
        {{ x = -2; y = 1; z = 0; intensity = 0.5; color = {{ r = 255; g = 244; b = 214; }}; }}
    );
    directional = (
        {{ x = 0.5; y = -1; z = -0.5; }}
    );
}};
"""


def create_ppm_files(img):
    for i in tqdm(range(img), desc="Creating PPM files"):
        os.system(f"./raytracer scenes/config_animation/{i:02}.cfg -w > scenes/config_animation/{i:02}.ppm")
    print("PPM files created")

def convert_to_gif(img):
    for i in tqdm(range(img), desc="Converting to PNG"):
        os.system(f"magick scenes/config_animation/{i:02}.ppm scenes/config_animation/{i:02}.png")
    sleep(1)
    os.system("magick -delay 5 -loop 0 scenes/config_animation/*.png scenes/scene.gif")
    sleep(1)
    os.system("rm scenes/config_animation/*")
    print("GIF file created [scene.gif]")

if __name__ == "__main__":
    img = 50
    if sys.argv[1] == "--shpere":
        create_config_files_spheres(img)
    elif sys.argv[1] == "--cone":
        create_config_files_cones(img)
    elif sys.argv[1] == "--cylinder":
        create_config_files_cylinders(img)
    create_ppm_files(img)
    convert_to_gif(img)
