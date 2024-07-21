#include <random>
#include "simulation.h"

Simulation::Simulation(int particleCount, SDL_Rect initialArea) : particles(std::vector<Particle>(particleCount)) {
    std::random_device rd;

    for (auto &particle: particles) {
        particle.position.x = static_cast<float>(rd() % initialArea.w + initialArea.x);
        particle.position.y = static_cast<float>(rd() % initialArea.h + initialArea.y);
    }
}

void Simulation::updateSimulation() {
    if (SDL_GetTicks() - lastTime < targetDelaT) {
        return;
    }

    auto deltaTime = static_cast<float>(SDL_GetTicks() - lastTime) / 1000.0f;

    for (auto &particle: particles) {
        particle.calcLoads();
        particle.updateBodyEuler(deltaTime);
    }
}

void Simulation::draw() {
    for (auto &particle: particles) {
        particle.draw();
    }
}
