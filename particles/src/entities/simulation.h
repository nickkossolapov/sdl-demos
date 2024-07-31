#ifndef PARTICLES_SIMULATION_H
#define PARTICLES_SIMULATION_H

#include <random>
#include <vector>

#include "obstacle.h"
#include "particle.h"
#include "../config/config.h"

class Simulation {
public:
    Simulation(int particleCount, SDL_Rect initialArea, int obstacleCount, SDL_Rect obstacleArea);

    void updateSimulation();

    void draw() const;

    bool checkForCollision(Particle &particle, float timeStep);

private:
    std::vector<Particle> particles;
    std::vector<Obstacle> obstacles;
    Uint32 lastTime = 0;
    float targetTimeStep = 0.005f;
    float accumulator = 0.0f;
    std::mt19937 rng; // Use Mersenne Twister for better performance
    static constexpr float particleRadius = 3;
    static constexpr float obstacleRadius = 30;
    static constexpr float collisionRadius = particleRadius + obstacleRadius;
};


#endif //PARTICLES_SIMULATION_H
