#include <random>
#include "simulation.h"

Simulation::Simulation(int particleCount, SDL_Rect initialArea) : particles(std::vector<Particle>(particleCount)) {
    std::random_device rd;

    for (auto &particle: particles) {
        particle = Particle();
        particle.position.x = static_cast<float>(rd() % initialArea.w + initialArea.x);
        particle.position.y = static_cast<float>(rd() % initialArea.h + initialArea.y);
    }
}

void Simulation::updateSimulation() {}

void Simulation::draw() {
    for (auto &particle: particles) {
        particle.draw();
    }
}
