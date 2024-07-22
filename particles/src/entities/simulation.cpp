#include <random>
#include "simulation.h"

Simulation::Simulation(int particleCount, SDL_Rect initialArea, int obstacleCount, SDL_Rect obstacleArea)
    : particles(std::vector<Particle>(particleCount))
{
    std::random_device rd;

    for (auto& particle : particles)
    {
        particle.position.x = static_cast<float>(rd() % initialArea.w + initialArea.x);
        particle.position.y = static_cast<float>(rd() % initialArea.h + initialArea.y);
    }


    for (int i = 0; i < obstacleCount; i++)
    {
        Vector position
        {
            static_cast<float>(rd() % obstacleArea.w + obstacleArea.x),
            static_cast<float>(rd() % obstacleArea.h + obstacleArea.y)
        };

        obstacles.emplace_back(position);
    }
}

void Simulation::updateSimulation()
{
    const Uint32 currentTime = SDL_GetTicks();
    float frameTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    accumulator += frameTime;

    while (accumulator >= targetTimeStep)
    {
        for (auto& particle : particles)
        {
            particle.isColliding = checkForCollision(particle, targetTimeStep);
            particle.calcLoads();
            particle.updateBodyEuler(targetTimeStep);
        }
        accumulator -= targetTimeStep;
    }

    lastTime = SDL_GetTicks();
}

void Simulation::draw() const
{
    for (auto& particle : particles)
    {
        particle.draw();
    }

    for (auto& obstable : obstacles)
    {
        obstable.draw();
    }
}

bool Simulation::checkForCollision(Particle& particle, float timeStep)
{
    particle.impactForce = {0.0f, 0.0f};
    bool isColliding = false;

    // Check for ground plane collision
    if (particle.position.y <= World::groundPlane + particle.radius + 0.05f)
    {
        float normalVelocity = particle.velocity.dot({0.0f, 1.0f});

        if (normalVelocity < 0.0f)
        {
            float J = -normalVelocity * particle.mass * (particle.restitution + 1.0f);

            if (J < 0.05f)
            {
                J = 0.0f;
            }

            particle.impactForce = {0.0f, J / timeStep};
            particle.position.y = particle.previousPosition.y;

            isColliding = true;
        }
    }

    return isColliding;
}
