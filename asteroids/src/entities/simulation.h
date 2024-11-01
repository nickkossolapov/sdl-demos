#ifndef PARTICLES_SIMULATION_H
#define PARTICLES_SIMULATION_H

#include <vector>

#include "body2d.h"
#include "../config/config.h"

class Simulation {
public:
    explicit Simulation(const std::vector<std::reference_wrapper<Body2d> > &_gameObjects) : gameObjects(_gameObjects) {
    };

    void updateSimulation();

private:
    std::vector<std::reference_wrapper<Body2d> > gameObjects;
    Uint32 lastTime = 0;
    float targetTimeStep = 0.005f;
    float accumulator = 0.0f;
    // std::mt19937 rng; // Use Mersenne Twister for better performance
};


#endif //PARTICLES_SIMULATION_H
