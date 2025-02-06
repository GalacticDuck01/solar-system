#pragma once

#include <godot_cpp/classes/mesh_instance3d.hpp>

using namespace godot;

class Icosphere : public MeshInstance3D {
    GDCLASS(Icosphere, MeshInstance3D);

    int resolution;

protected:
    static void _bind_methods();

public:
    Icosphere() { resolution = 3; }

    int GetResolution() { return resolution; }
    void SetResolution(int res) { resolution = res; }
};