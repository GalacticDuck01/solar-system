#include "Planet.hpp"

Planet::Planet() : Icosphere() {
    path = memnew(Path3D);
    trajectory.instantiate();
    trajectoryMesh = memnew(MeshInstance3D);
}

void Planet::_ready() {
    Icosphere::_ready();

    radius = 5.f;
    set_scale(Vector3(radius, radius, radius));

    print_line("Planet created");

    SetPosition(Vector3(5, 0, 0));

    Vector3 v = sqrt(G*M/position.length()) * vec3_cross(position, Vector3(0, 1, 0)).normalized();
    SetVelocity(v);

    P = 2*Math_PI*position.length()/velocity.length();

    print_line("Period: " + String::num(P, 2));

    states = {
        position.x,
        position.y,
        position.z,
        velocity.x,
        velocity.y,
        velocity.z
    };

    float t = 0.f;
    while (t < P) {
        // RK4 method
        std::vector<float> prevState(states.end() - 6, states.end());
        Vector3 r0(prevState[0], prevState[1], prevState[2]);
        Vector3 v0(prevState[3], prevState[4], prevState[5]);

        Vector3 k1, k2, k3, k4;

        k1 = h*v0;
        k2 = h*(v0 + k1/2);
        k3 = h*(v0 + k2/2);
        k4 = h*(v0 + k3);
        Vector3 r1 = r0 + (k1 + 2*k2 + 2*k3 + k4)/6;

        Vector3 a = CalcAcceleration(r0);
        k1 = h*a;
        k2 = h*(a + k1/2);
        k3 = h*(a + k2/2);
        k4 = h*(a + k3);
        Vector3 v1 = v0 + (k1 + 2*k2 + 2*k3 + k4)/6;

        states.insert(states.end(), {r1.x, r1.y, r1.z, v1.x, v1.y, v1.z});

        t += h;
    }

    trajectory->clear_surfaces();
    trajectory->surface_begin(Mesh::PRIMITIVE_LINE_STRIP);
    for (int i = 0; i < states.size()/6; i++) {
        trajectory->surface_add_vertex(Vector3(states[i*6+0], states[i*6+1], states[i*6+2]));
    }
    trajectory->surface_end();
    trajectoryMesh->set_mesh(trajectory);

    call_deferred("add_sibling", trajectoryMesh);
}

void Planet::_process(float delta) {
    float tSinceP = time - int(time/P)*P;
    int index = int(tSinceP/h);
    position = Vector3(states[index*6+0], states[index*6+1], states[index*6+2]);
    velocity = Vector3(states[index*6+3], states[index*6+4], states[index*6+5]);
    set_position(position);

    if (index >= )

    time += delta;
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