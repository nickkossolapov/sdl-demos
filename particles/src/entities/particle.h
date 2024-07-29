#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include <SDL.h>
#include "../math/Vector.h"
#include "../config/colors.h"

class Particle {
public:
    float mass;
    Vector position;
    Vector previousPosition;
    Vector velocity;
    float speed;
    Vector netForce;
    Vector impactForce;
    float radius;
    SDL_Color colour;
    bool isColliding = false;
    float restitution = 0.3;

    explicit Particle(float radius = 3, SDL_Color colour = Colours::blue);

    void calcLoads();

    void updateBodyEuler(float dt);

    void draw() const;

private:
    float dragCoefficient = 0.47;
    float area;
};

#endif //PARTICLES_PARTICLE_H
