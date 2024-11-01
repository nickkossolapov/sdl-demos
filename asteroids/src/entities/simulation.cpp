#include "simulation.h"

#include <SDL_timer.h>

void Simulation::updateSimulation() {
    const Uint32 currentTime = SDL_GetTicks();
    float frameTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    accumulator += frameTime;

    while (accumulator >= targetTimeStep) {
        for (auto &gameObject: gameObjects) {
            gameObject.get().updateBodyEuler(targetTimeStep);
        }

        accumulator -= targetTimeStep;
    }

    lastTime = SDL_GetTicks();
}
