#ifndef PARTICLES_SIMULATION_H
#define PARTICLES_SIMULATION_H

#include <SDL.h>
#include <vector>

#include "asteroidManager.h"
#include "../entities/body2d.h"
#include "bulletManager.h"
#include "../entities/spaceship.h"

class Simulation {
public:
    explicit Simulation(Spaceship &_spaceship, BulletManager &_bulletManager, AsteroidManager &_asteroidManager)
        : spaceship(_spaceship), bulletManager(_bulletManager), asteroidManager(_asteroidManager) {
    };

    void updateSimulation();

private:
    Uint32 lastTime = 0;
    float targetTimeStep = 0.005f;
    float accumulator = 0.0f;
    Spaceship &spaceship;
    BulletManager &bulletManager;
    AsteroidManager &asteroidManager;
};


#endif //PARTICLES_SIMULATION_H
