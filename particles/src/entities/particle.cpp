#include "particle.h"
#include "../constants.h"

Particle::Particle() {
    mass = 1.0;
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
    velocity.x = 0.0;
    velocity.y = 0.0;
    velocity.z = 0.0;
    speed = 0.0;
    netForce.x = 0.0;
    netForce.y = 0.0;
    netForce.z = 0.0;
    radius = 0.1;
}

void Particle::calcLoads() {
    netForce.y = Constants::Gravity * mass;
}

void Particle::updateBodyEuler(float dt) {
    Vector a = netForce / mass;
    Vector dv = a * dt;
    velocity += dv;

    Vector ds = velocity * dt;
    position += ds;

    speed = velocity.length();
}
