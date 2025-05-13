#include "Obj.hpp"
#include <cmath>
#include "../../include/IMaterial.hpp"

using namespace RayTracer;

Obj::Obj() : _vertices(), _faces(), _offset(0,0,0), _material(nullptr) {}

void Obj::setPath(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Obj plugin: cannot open file " + path);

    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("v ", 0) == 0) {
            std::istringstream iss(line.substr(2));
            double x, y, z;
            iss >> x >> y >> z;
            _vertices.emplace_back(x, y, z);
        }
        else if (line.rfind("f ", 0) == 0) {
            std::istringstream iss(line.substr(2));
            std::string va, vb, vc;
            iss >> va >> vb >> vc;
            auto idx = [](const std::string &s) {
                auto p = s.find('/');
                return std::stoi( p == std::string::npos ? s : s.substr(0, p) );
            };
            int i = idx(va), j = idx(vb), k = idx(vc);
            _faces.push_back({ i - 1, j - 1, k - 1 });
        }
    }
}



bool Obj::intersect(const Ray &ray, double &t, Math::Point3D &hitPoint, Math::Vector3D &normal) const
{
    bool hit = false;
    double tMin = std::numeric_limits<double>::max();
    Math::Vector3D bestN;

    for (const auto &f : _faces) {
        Math::Point3D a = _vertices[f.v0] + _offset;
        Math::Point3D b = _vertices[f.v1] + _offset;
        Math::Point3D c = _vertices[f.v2] + _offset;
        double tTri;
        Math::Vector3D nTri;
        if (intersectTriangle(ray, a, b, c, tTri, nTri) && tTri < tMin) {
            hit = true;
            tMin = tTri;
            bestN = nTri;
        }
    }

    if (hit) {
        t = tMin;
        hitPoint = ray.origin + ray.direction * t;
        normal = bestN;
    }
    return hit;
}

bool Obj::intersectTriangle(const Ray &ray,
    const Math::Point3D &v0,
    const Math::Point3D &v1,
    const Math::Point3D &v2,
    double &t, Math::Vector3D &normalOut) const
{
    const double EPS = 1e-8;
    Math::Vector3D edge1 = v1 - v0;
    Math::Vector3D edge2 = v2 - v0;
    Math::Vector3D P(
        ray.direction.y * edge2.z - ray.direction.z * edge2.y,
        ray.direction.z * edge2.x - ray.direction.x * edge2.z,
        ray.direction.x * edge2.y - ray.direction.y * edge2.x
    );
    double det = edge1.dot(P);
    if (std::fabs(det) < EPS) return false;
    double invDet = 1.0 / det;
    Math::Vector3D T = ray.origin - v0;
    double u = T.dot(P) * invDet;
    if (u < 0.0 || u > 1.0) return false;
    Math::Vector3D Q(
        T.y * edge1.z - T.z * edge1.y,
        T.z * edge1.x - T.x * edge1.z,
        T.x * edge1.y - T.y * edge1.x
    );
    double v = ray.direction.dot(Q) * invDet;
    if (v < 0.0 || u + v > 1.0) return false;
    double tTemp = edge2.dot(Q) * invDet;
    if (tTemp > EPS) {
        t = tTemp;
        Math::Vector3D N(
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x
        );
        normalOut = N / N.length();
        return true;
    }
    return false;
}

extern "C" std::unique_ptr<IPrimitive> create()
{
    return std::make_unique<Obj>();
}
