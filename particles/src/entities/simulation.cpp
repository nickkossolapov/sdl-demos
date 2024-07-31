#include <random>
#include "simulation.h"

Simulation::Simulation(int particleCount, SDL_Rect initialArea, int obstacleCount, SDL_Rect obstacleArea)
        : particles(std::vector<Particle>(particleCount)) {
    std::random_device rd;

    for (auto &particle: particles) {
        particle.radius = particleRadius;
        particle.position.x = static_cast<float>(rd() % initialArea.w + initialArea.x);
        particle.position.y = static_cast<float>(rd() % initialArea.h + initialArea.y);
    }


    for (int i = 0; i < obstacleCount; i++) {
        Vector position
                {
                        static_cast<float>(rd() % obstacleArea.w + obstacleArea.x),
                        static_cast<float>(rd() % obstacleArea.h + obstacleArea.y)
                };

        obstacles.emplace_back(position, obstacleRadius);
    }
}

void Simulation::updateSimulation() {
    const Uint32 currentTime = SDL_GetTicks();
    float frameTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    accumulator += frameTime;

    while (accumulator >= targetTimeStep) {
        for (auto &particle: particles) {
            particle.isColliding = checkForCollision(particle, targetTimeStep);
            particle.calcLoads();
            particle.updateBodyEuler(targetTimeStep);
        }
        accumulator -= targetTimeStep;
    }

    lastTime = SDL_GetTicks();
}

void Simulation::draw() const {
    for (auto &particle: particles) {
        particle.draw();
    }

    for (auto &obstable: obstacles) {
        obstable.draw();
    }
}

bool Simulation::checkForCollision(Particle &particle, float timeStep) {
    particle.impactForce = {0.0f, 0.0f};
    bool isColliding = false;

    // check for multiple collisions
    int numCollisions = 0;

    // Check for ground plane collision
    if (particle.position.y <= World::groundPlane + particle.radius) {
        float normalVelocity = particle.velocity.dot({0.0f, 1.0f});

        if (normalVelocity < 0.0f) {
            float J = -normalVelocity * particle.mass * (particle.restitution + 1.0f);

            particle.impactForce = {0.0f, J / timeStep};
            particle.position.y = particle.previousPosition.y;

            isColliding = true;
            ++numCollisions;
        }
    }

    // Check for left wall collision
    if (particle.position.x <= 0 + particle.radius) {
        float normalVelocity = particle.velocity.dot({1.0f, 0.0f});

        if (normalVelocity < 0.0f) {
            float J = -normalVelocity * particle.mass * (particle.restitution + 1.0f);

            particle.impactForce += {J / timeStep, 0.0f};
            particle.position.x = particle.previousPosition.x;

            isColliding = true;
            ++numCollisions;
        }
    }

    // Check for right wall collision
    if (particle.position.x >= ScreenSize::width - particle.radius - 0.05f) {
        float normalVelocity = particle.velocity.dot({-1.0f, 0.0f});

        if (normalVelocity < 0.0f) {
            float J = -normalVelocity * particle.mass * (particle.restitution + 1.0f);

            particle.impactForce = {-J / timeStep, 0.0f};
            particle.position.x = particle.previousPosition.x;

            isColliding = true;
            ++numCollisions;
        }
    }

    // Check for obstacle collision
    for (auto &obstacle: obstacles) {
        Vector distance = (particle.position - obstacle.position);
        float overlap = distance.length() - collisionRadius;

        if (overlap < 0) {
            distance.normalize();

            float normalVelocity = particle.velocity.dot(distance);

            if (normalVelocity < 0.0f) {
                Vector J = -distance * normalVelocity * particle.mass * (particle.restitution + 1.0f);

                particle.impactForce += J / timeStep;
                particle.position -= distance * overlap;

                isColliding = true;
                ++numCollisions;
            }
        }
    }

    // Split mass if collisions multiple collisions are detected - https://gamedev.stackexchange.com/a/32614
    // Since only one particle can collide with multiple objects, mass and impulse force are directly related
    if (numCollisions > 1) {
        particle.impactForce /= static_cast<float>(numCollisions);
    }

    return isColliding;
}
