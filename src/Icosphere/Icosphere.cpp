#include "Icosphere.hpp"

#include <godot_cpp/core/class_db.hpp>

void Icosphere::_bind_methods() {
    ClassDB::bind_method(D_METHOD("GetResolution"), &Icosphere::GetResolution);
    ClassDB::bind_method(D_METHOD("SetResolution", "newResolution"), &Icosphere::SetResolution);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "resolution"), "SetResolution", "GetResolution");
}