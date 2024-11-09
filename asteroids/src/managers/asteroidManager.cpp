#include "asteroidManager.h"

#include <chrono>

#include "../config/config.h"

AsteroidManager::AsteroidManager(int const initialAsteroids, BulletManager &_bulletManager)
        : bulletManager(_bulletManager),
          rng(std::chrono::system_clock::now().time_since_epoch().count()) {
    for (int i = 0; i < initialAsteroids; ++i) {
        createAsteroid();
    }
}

void AsteroidManager::update() {
    for (auto &asteroid: asteroids) {
        asteroid.update();

        for (auto &bullet: bulletManager.getBullets()) {
            if (asteroid.isColliding(bullet.position)) {
                asteroid.hasCollided = true;
                bullet.isDestroyed = true;
                break;
            }
        }
    }

    for (int i = 0; i < asteroids.size();) {
        if (asteroids[i].hasCollided || (asteroids[i].hasAppeared && asteroids[i].isOffScreen())) {
            std::swap(asteroids[i], asteroids.back());
            asteroids.pop_back();
            createAsteroid();
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
    auto scale = scaleDist(rng);

    auto asteroid = Asteroid(scale, rng);

    std::uniform_real_distribution<float> xDist(0, ScreenSize::width);
    std::uniform_real_distribution<float> yDist(0, ScreenSize::height);
    std::uniform_real_distribution<float> speedDist(-0.8, 0.8);
    std::normal_distribution<float> spinDist(0, 2);
    std::uniform_int_distribution<short> faceDist(0, 3);

    float speed = std::sqrt(static_cast<float>(scale));
    short face = faceDist(rng);

    switch (face) {
        case 0: // top
            asteroid.position = {xDist(rng), -asteroid.radius};
            asteroid.velocity = {speedDist(rng) * 2, 1};
            break;
        case 1: // right
            asteroid.position = {ScreenSize::width + asteroid.radius, yDist(rng)};
            asteroid.velocity = {-1, speedDist(rng) * 2};
            break;
        case 2: // bottom
            asteroid.position = {xDist(rng), ScreenSize::height + asteroid.radius};
            asteroid.velocity = {speedDist(rng) * 2, -1};
            break;
        case 3: // left
            asteroid.position = {-asteroid.radius, yDist(rng)};
            asteroid.velocity = {1, speedDist(rng) * 2};
            break;
        default:
            break;
    }

    Vector center = {ScreenSize::width / 2.0f, ScreenSize::height / 2.0f};
    Vector directionToCenter = center - asteroid.position;
    directionToCenter.normalize();

    // Adjust velocity to move towards the center a bit
    asteroid.velocity += directionToCenter * 2.0f; // Adjust the factor as needed
    asteroid.velocity.normalize();

    asteroid.velocity *= 200.0f / speed;

    asteroid.angularVelocity = std::max(std::min(spinDist(rng), 2.0f), -2.0f);

    asteroids.push_back(asteroid);
}


