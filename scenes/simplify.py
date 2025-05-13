#!/usr/bin/env python3
import sys

def simplify_obj(input_path, output_path, keep_ratio):
    verts = []
    faces = []
    with open(input_path, 'r') as f:
        for line in f:
            if line.startswith('v '):
                verts.append(line)
            elif line.startswith('f '):
                faces.append(line)
    step = max(1, int(1 / keep_ratio))
    kept_faces = faces[::step]
    used = set()
    for L in kept_faces:
        for token in L.strip().split()[1:]:
            used.add(int(token.split('/')[0]))
    old2new = {}
    new_verts = []
    for old in sorted(used):
        old2new[old] = len(new_verts) + 1
        new_verts.append(verts[old - 1])
    with open(output_path, 'w') as out:
        for v in new_verts:
            out.write(v)
        out.write('\n')
        for L in kept_faces:
            idxs = [t.split('/')[0] for t in L.strip().split()[1:]]
            new_idxs = [str(old2new[int(i)]) for i in idxs]
            out.write('f ' + ' '.join(new_idxs) + '\n')

    print(f"→ {len(new_verts)} sommets, {len(kept_faces)} faces écrits dans {output_path}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: simplify_obj.py in.obj out.obj ratio")
        sys.exit(1)
    simplify_obj(sys.argv[1], sys.argv[2], float(sys.argv[3]))
