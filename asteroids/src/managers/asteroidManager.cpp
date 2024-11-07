#include "asteroidManager.h"

void AsteroidManager::update() {
    asteroids[0].orientation += 0.05;
}

void AsteroidManager::updateBodiesEuler(const float dt) const {
    for (auto asteroid: asteroids) {
        asteroid.updateBodyEuler(dt);
    }
}

void AsteroidManager::drawAsteroids() const {
    for (const auto &asteroid: asteroids) {
        asteroid.draw();
    }
}


