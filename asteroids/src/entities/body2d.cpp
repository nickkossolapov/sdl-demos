#include <stdexcept>

#include "body2d.h"
#include "../math/utils.h"

Body2d::Body2d(float mass, float inertia) : mass(mass), inertia(inertia) {
    if (inertia < 0) {
        throw std::invalid_argument("intertia cannot be negative");
    }

    if (mass < 0) {
        throw std::invalid_argument("mass cannot be negative");
    }
}

void Body2d::updateBodyEuler(float dt) {
    Vector a = netForce / mass;
    Vector dv = a * dt;

    velocity += dv;

    speed = velocity.length();

    if (speed > maxSpeed) {
        speed = maxSpeed;
        velocity.normalize();
        velocity *= speed;
    }

    Vector ds = velocity * dt;
    position += ds;

    float aa = netMoment / inertia;
    float dav = aa * aa;
    angularVelocity += dav;

    float dr = angularVelocity * dt;
    orientation += dr;
}
