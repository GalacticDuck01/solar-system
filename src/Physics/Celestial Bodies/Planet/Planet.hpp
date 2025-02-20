#pragma once

#include "Icosphere.hpp"

#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/path3d.hpp>
#include <godot_cpp/classes/curve3d.hpp>
#include <math.h>

using namespace godot;

class Planet : public Icosphere {
    GDCLASS(Planet, Icosphere);

private:
    float radius;
    Vector3 position;
    Vector3 velocity;
    int N;
    float h = 0.001f;
    std::vector<float> states;

    float P;
    float time = 0.f;

    Path3D* path;
    Ref<ImmediateMesh> trajectory;
    MeshInstance3D* trajectoryMesh;

    float G = 1.f;
    float M = 5.f;

    Vector3 CalcAcceleration(Vector3 p) {
        // Acceleration acting on body due to body of mass M:
        // \frac{d^2 r}{dt^2} = - \frac{GM}{|r|^2} \hat{r}
        return -(G*M)/p.length_squared() * p.normalized();
    }

protected:
    static void _bind_methods();

public:
    Planet();
    void _ready() override;
    void _process(float delta);

    float GetRadius() { return radius; }
    void SetRadius(int newRadius) { radius = newRadius; set_scale(Vector3(radius, radius, radius)); }
    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 newPosition) { position = newPosition; set_position(position); }
    Vector3 GetVelocity() { return velocity; }
    void SetVelocity(Vector3 newVelocity) { velocity = newVelocity;}
};