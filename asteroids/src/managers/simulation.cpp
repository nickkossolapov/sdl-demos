#include "simulation.h"

#include <SDL_timer.h>

void Simulation::updateSimulation() {
    if (paused) {
        lastTime = SDL_GetTicks();
        return;
    }

    const Uint32 currentTime = SDL_GetTicks();
    float frameTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    accumulator += frameTime;

    while (accumulator >= targetTimeStep) {
        spaceship.updateBodyEuler(targetTimeStep);
        asteroidManager.updateBodiesEuler(targetTimeStep);
        bulletManager.updateBullets(targetTimeStep);

        accumulator -= targetTimeStep;
    }

    lastTime = SDL_GetTicks();
}
