import os
import math
from tqdm import tqdm
from time import sleep

def congif(x1, y1, z1, x2, y2, z2):
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

def create_config_files(img):
    cx, cy, cz =  0.0, 1.5, -6.5
    R = 6.0

    for i in range(img):
        theta = 2 * math.pi * i / img
        x1 = cx + R * math.cos(theta)
        z1 = cz + R * math.sin(theta)
        x2 = cx + R * math.cos(theta + math.pi)
        z2 = cz + R * math.sin(theta + math.pi)

        cfg = congif(x1, cy, z1, x2, cy, z2)
        with open(f"scenes/config_gif/{i:02}.cfg", "w") as f:
            f.write(cfg)
    print("Config files created for dual orbit")

def create_ppm_files(img):
    for i in tqdm(range(img), desc="Creating PPM files"):
        os.system(f"./raytracer scenes/config_gif/{i:02}.cfg -w > scenes/config_gif/{i:02}.ppm")
    print("PPM files created")

def convert_to_gif(img):
    for i in tqdm(range(img), desc="Converting to PNG"):
        os.system(f"magick scenes/config_gif/{i:02}.ppm scenes/config_gif/{i:02}.png")
    sleep(1)
    os.system("magick -delay 5 -loop 0 scenes/config_gif/*.png scene.gif")
    sleep(1)
    os.system("rm scenes/config_gif/*")
    print("GIF file created [scene.gif]")

if __name__ == "__main__":
    img = 50
    create_config_files(img)
    create_ppm_files(img)
    convert_to_gif(img)
