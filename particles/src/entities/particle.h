#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include <SDL.h>
#include "../math/Vector.h"
#include "../config/colors.h"

class Particle {
public:
    float mass;
    Vector position;
    Vector velocity;
    float speed;
    Vector netForce;
    float radius;
    SDL_Color colour;


    explicit Particle(float radius = 3, SDL_Color colour = Colours::blue);

    void calcLoads();

    void updateBodyEuler(float dt);

    void draw() const;
};

#endif //PARTICLES_PARTICLE_H
