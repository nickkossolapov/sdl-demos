#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include "../math/Vector.h"

class Particle {
public:
    float mass;
    Vector position;
    Vector velocity;
    float speed;
    Vector netForce;
    float radius;


    Particle();

    void calcLoads();

    void updateBodyEuler(float dt);

    void draw();
};

#endif //PARTICLES_PARTICLE_H
