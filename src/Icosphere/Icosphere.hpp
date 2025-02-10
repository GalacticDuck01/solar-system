#pragma once

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>

#include <unordered_map>

using namespace godot;

class Icosphere : public MeshInstance3D {
    GDCLASS(Icosphere, MeshInstance3D);

private:
    int resolution;
    std::vector<Vector3> vertices;

    void GenerateIcosphere();
    int CreateNewMidpoint(int v1, int v2);

protected:
    static void _bind_methods();

public:
    Icosphere();
    void _ready() override;

    int GetResolution() { return resolution; }
    void SetResolution(int res);
};