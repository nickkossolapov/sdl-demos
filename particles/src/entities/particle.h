#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include <SDL.h>
#include "../math/Vector.h"

class Particle {
public:
    float mass;
    Vector position;
    Vector velocity;
    float speed;
    Vector netForce;
    float radius;
    SDL_Color colour;


    Particle();

    void calcLoads();

    void updateBodyEuler(float dt);

    void draw();
};

#endif //PARTICLES_PARTICLE_H
