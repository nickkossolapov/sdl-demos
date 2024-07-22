#ifndef PARTICLES_SIMULATION_H
#define PARTICLES_SIMULATION_H

#include <vector>

#include "obstacle.h"
#include "particle.h"
#include "../config/config.h"

class Simulation
{
public:
    Simulation(int particleCount, SDL_Rect initialArea, int obstacleCount, SDL_Rect obstacleArea);

    void updateSimulation();

    void draw() const;

    static bool checkForCollision(Particle& particle, float timeStep);

private:
    std::vector<Particle> particles;
    std::vector<Obstacle> obstacles;
    Uint32 lastTime = 0;
    float targetTimeStep = 0.005f;
    float accumulator = 0.0f;
};


#endif //PARTICLES_SIMULATION_H
