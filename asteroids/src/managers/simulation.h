#ifndef ASTEROIDS_SIMULATION_H
#define ASTEROIDS_SIMULATION_H

#include <SDL.h>
#include <vector>

#include "asteroidManager.h"
#include "../entities/body2d.h"
#include "bulletManager.h"
#include "../entities/player.h"

class Simulation {
public:
    explicit Simulation(Player& _spaceship, BulletManager& _bulletManager, AsteroidManager& _asteroidManager)
        : spaceship(_spaceship), bulletManager(_bulletManager), asteroidManager(_asteroidManager) {};

    void updateSimulation();

    void pause(bool value) {
        paused = value;
    }

private:
    Uint32 lastTime = 0;
    float targetTimeStep = 0.005f;
    float accumulator = 0.0f;
    Player& spaceship;
    BulletManager& bulletManager;
    AsteroidManager& asteroidManager;
    bool paused = true;
};


#endif //ASTEROIDS_SIMULATION_H
