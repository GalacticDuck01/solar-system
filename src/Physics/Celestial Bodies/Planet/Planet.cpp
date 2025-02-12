#include "Planet.hpp"

Planet::Planet() : Icosphere() {
    radius = 5;
}

void Planet::_ready() {
    Icosphere::_ready();
}

void Planet::_bind_methods() {
    ClassDB::bind_method(D_METHOD("GetRadius"), &Planet::GetRadius);
    ClassDB::bind_method(D_METHOD("SetRadius", "newRadius"), &Planet::SetRadius);
    ClassDB::bind_method(D_METHOD("GetPosition"), &Planet::GetPosition);
    ClassDB::bind_method(D_METHOD("SetPosition", "newPosition"), &Planet::SetPosition);
    ClassDB::bind_method(D_METHOD("GetVelocity"), &Planet::GetVelocity);
    ClassDB::bind_method(D_METHOD("SetVelocity", "newVelocity"), &Planet::SetVelocity);

    Icosphere::_bind_methods();
}