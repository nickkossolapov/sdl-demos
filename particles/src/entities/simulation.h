#ifndef PARTICLES_SIMULATION_H
#define PARTICLES_SIMULATION_H

#include <vector>
#include "particle.h"
#include "../config/config.h"

class Simulation {
public:
    Simulation(int particleCount, SDL_Rect initialArea);

    void updateSimulation();

    void draw();

private:
    std::vector<Particle> particles;
    Uint32 lastTime = 0;
    int targetDelaT = 0;
};


#endif //PARTICLES_SIMULATION_H
