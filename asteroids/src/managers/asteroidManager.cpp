#include "asteroidManager.h"

void AsteroidManager::update() {
    asteroids[0].orientation += 0.05;

    for (auto &asteroid: asteroids) {
        for (const auto &bullet: bulletManager.getBullets()) {
            if (asteroid.isColliding(bullet.position)) {
                asteroid.hasCollided = true;
                return;
            }
        }
    }
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


