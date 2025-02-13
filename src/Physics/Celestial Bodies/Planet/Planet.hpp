#pragma once

#include "Icosphere.hpp"

using namespace godot;

class Planet : public Icosphere {
    GDCLASS(Planet, Icosphere);

private:
    float radius;
    Vector3 position;
    Vector3 velocity;

protected:
    static void _bind_methods();

public:
    Planet();
    void _ready() override;

    float GetRadius() { return radius; }
    void SetRadius(int newRadius) { radius = newRadius; set_scale(Vector3(radius, radius, radius)); }
    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 newPosition) { position = newPosition; }
    Vector3 GetVelocity() { return velocity; }
    void SetVelocity(Vector3 newVelocity) { velocity = newVelocity; }
};