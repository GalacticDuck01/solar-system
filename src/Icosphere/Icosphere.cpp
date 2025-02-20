#include "Icosphere.hpp"

#include <godot_cpp/core/class_db.hpp>

Icosphere::Icosphere() {}

void Icosphere::_ready() {
    resolution = 5;
    GenerateIcosphere();
}

void Icosphere::GenerateIcosphere() {
    Ref<ArrayMesh> mesh = get_mesh();

    Ref<Material> existingMaterial;

    if (mesh.is_valid()) {
        if (mesh->get_surface_count() > 0) existingMaterial = mesh->surface_get_material(0);

        UtilityFunctions::print("Clearing mesh");
        mesh->clear_surfaces();
    } else {
        UtilityFunctions::print("Initialising mesh");
        mesh.instantiate();
    }

    Ref<SurfaceTool> surfaceTool;
    surfaceTool.instantiate();
    surfaceTool->begin(Mesh::PRIMITIVE_TRIANGLES);

    struct TriangleIndices {
        int i1, i2, i3;
    };

    vertices.clear();

    // Create the icosphere, very nicely sourced from http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
    const float t = (1.0f + sqrt(5.0f)) / 2.0f; // Golden ratio
    vertices = {
        Vector3(-1,  t,  0).normalized(),
        Vector3( 1,  t,  0).normalized(),
        Vector3(-1, -t,  0).normalized(),
        Vector3( 1, -t,  0).normalized(),
        Vector3( 0, -1,  t).normalized(),
        Vector3( 0,  1,  t).normalized(),
        Vector3( 0, -1, -t).normalized(),
        Vector3( 0,  1, -t).normalized(),
        Vector3( t,  0, -1).normalized(),
        Vector3( t,  0,  1).normalized(),
        Vector3(-t,  0, -1).normalized(),
        Vector3(-t,  0,  1).normalized()
    };

    std::vector<TriangleIndices> triangles = {
        {0, 11, 5},
        {0,  5, 1},
        {0,  1, 7},
        {0,  7, 10},
        {0, 10, 11},
        {1,  5, 9},
        {5,  11, 4},
        {11, 10, 2},
        {10, 7, 6},
        {7, 1, 8},
        {3, 9, 4},
        {3, 4, 2},
        {3, 2, 6},
        {3, 6, 8},
        {3, 8, 9},
        {4, 9, 5},
        {2, 4, 11},
        {6, 2, 10},
        {8, 6, 7},
        {9, 8, 1}
    };

    int i1, i2, i3, i12, i13, i23;
    for (int i = 0; i < resolution; i++) {
        std::vector<TriangleIndices> newTriangles;
        for (const auto& tri : triangles) {
            i1 = tri.i1;
            i2 = tri.i2;
            i3 = tri.i3;
            i12 = CreateNewMidpoint(i1, i2);
            i13 = CreateNewMidpoint(i1, i3);
            i23 = CreateNewMidpoint(i2, i3);

            newTriangles.push_back({i1,  i12, i13});
            newTriangles.push_back({i13, i12, i23});
            newTriangles.push_back({i12,  i2, i23});
            newTriangles.push_back({i13, i23, i3});
        }
        triangles = newTriangles;
    }

    for (const auto& tri : triangles) {
        Vector3 v1 = vertices[tri.i1];
        Vector3 v2 = vertices[tri.i2];
        Vector3 v3 = vertices[tri.i3];

        Vector3 normal = ((v2 - v1).cross(v3 - v1)).normalized();

        surfaceTool->set_normal(normal);
        surfaceTool->add_vertex(v3);

        surfaceTool->set_normal(normal);
        surfaceTool->add_vertex(v2);

        surfaceTool->set_normal(normal);
        surfaceTool->add_vertex(v1);
    }

    surfaceTool->commit(mesh);

    // Set material
    if (existingMaterial.is_valid()) {
        mesh->surface_set_material(0, existingMaterial);
    }

    set_mesh(mesh);
}

int Icosphere::CreateNewMidpoint(int i1, int i2) {
    // Not found, so calculate middle point
    Vector3 v1 = vertices[i1];
    Vector3 v2 = vertices[i2];
    Vector3 midpoint = (v1 + v2) / 2.0f;
    midpoint.normalize();
    // Get index before adding new vertex
    // E.g. if we add the 13th vertex (the first new one), we want to return 12
    int index = vertices.size();
    vertices.push_back(midpoint);
    return index;
}

void Icosphere::SetResolution(int res) {
    resolution = res;
    GenerateIcosphere();
}

void Icosphere::_bind_methods() {
    ClassDB::bind_method(D_METHOD("GetResolution"), &Icosphere::GetResolution);
    ClassDB::bind_method(D_METHOD("SetResolution", "newResolution"), &Icosphere::SetResolution);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "resolution", PROPERTY_HINT_RANGE, "0,10,1"), "SetResolution", "GetResolution");
}