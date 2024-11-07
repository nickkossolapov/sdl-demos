#include "asteroidManager.h"

#include <chrono>

#include "../config/config.h"

AsteroidManager::AsteroidManager(int initialAsteroids, BulletManager &_bulletManager)
    : bulletManager(_bulletManager),
      rng(std::chrono::system_clock::now().time_since_epoch().count()) {
    std::uniform_int_distribution<> scaleDist(1, 3);

    for (int i = 0; i < initialAsteroids; ++i) {
        asteroids.emplace_back(scaleDist(rng));
    }

    std::uniform_real_distribution<float> xDist(0, ScreenSize::width);
    std::uniform_real_distribution<float> yDist(0, ScreenSize::height);
    std::uniform_real_distribution<float> spinDist(-2, 2);

    for (auto &asteroid: asteroids) {
        asteroid.position = {xDist(rng), yDist(rng)};
        asteroid.angularVelocity = spinDist(rng);
    }
}

void AsteroidManager::update() {
    for (auto &asteroid: asteroids) {
        for (auto &bullet: bulletManager.getBullets()) {
            if (asteroid.isColliding(bullet.position)) {
                asteroid.hasCollided = true;
                bullet.isDestroyed = true;

                createAsteroid();
                return;
            }
        }
    }

    for (int i = 0; i < asteroids.size();) {
        if (asteroids[i].hasCollided) {
            std::swap(asteroids[i], asteroids.back());
            asteroids.pop_back();
        } else {
            i++;
        }
    }
}

void AsteroidManager::updateBodiesEuler(const float dt) {
    for (auto &asteroid: asteroids) {
        asteroid.updateBodyEuler(dt);
    }
}

void AsteroidManager::drawAsteroids() const {
    for (const auto &asteroid: asteroids) {
        asteroid.draw();
    }
}

void AsteroidManager::createAsteroid() {
    std::uniform_int_distribution<> scaleDist(1, 3);

    asteroids.emplace_back(scaleDist(rng));

    std::uniform_real_distribution<float> xDist(0, ScreenSize::width);
    std::uniform_real_distribution<float> yDist(0, ScreenSize::height);
    std::uniform_real_distribution<float> spinDist(-2, 2);

    asteroids.back().position = {xDist(rng), yDist(rng)};
    asteroids.back().angularVelocity = spinDist(rng);
}


