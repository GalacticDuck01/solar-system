#include "Planet.hpp"

Planet::Planet() : Icosphere() {
    radius = 5.f;
    set_scale(Vector3(radius, radius, radius));
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

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius"), "SetRadius", "GetRadius");

    Icosphere::_bind_methods();
}