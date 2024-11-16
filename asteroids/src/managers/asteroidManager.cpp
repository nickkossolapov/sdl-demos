#include "asteroidManager.h"

#include <chrono>

#include "../config/config.h"
#include "../globals.h"

AsteroidManager::AsteroidManager(int const initialAsteroids, BulletManager &_bulletManager, Score &_score,
                                 Player &_player)
        : bulletManager(_bulletManager), score(_score), player(_player),
          rng(std::chrono::system_clock::now().time_since_epoch().count()) {
    for (int i = 0; i < initialAsteroids; ++i) {
        createAsteroid();
    }
}

void AsteroidManager::update() {
    for (auto &asteroid: asteroids) {
        asteroid.update();

        for (auto &bullet: bulletManager.getBullets()) {
            if (asteroid.isColliding(bullet.position) && !bullet.isDestroyed) {
                asteroid.hasCollided = true;
                bullet.isDestroyed = true;
                break;
            }
        }
    }

    for (int i = 0; i < asteroids.size();) {
        if (asteroids[i].hasCollided) {
            score.increment(asteroids[i].scale);
            createAsteroidFragments(asteroids[i].scale, asteroids[i].position, asteroids[i].velocity);
            std::swap(asteroids[i], asteroids.back());
            asteroids.pop_back();
        } else if (asteroids[i].hasAppeared && asteroids[i].isOffScreen()) {
            std::swap(asteroids[i], asteroids.back());
            asteroids.pop_back();
            createAsteroid();
        } else {
            i++;
        }
    }
}

void AsteroidManager::checkCollisionWithPlayer(Asteroid &asteroid) {

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

    // Adjust velocity to move towards the center so that the asteroid doesn't just fly off the screen
    Vector center = {ScreenSize::width / 2.0f, ScreenSize::height / 2.0f};
    Vector directionToCenter = center - asteroid.position;
    directionToCenter.normalize();

    asteroid.velocity += directionToCenter * 2.0f;
    asteroid.velocity.normalize();
    asteroid.velocity *= 200.0f / speed;

    asteroid.angularVelocity = std::max(std::min(spinDist(rng), 2.0f), -2.0f);

    asteroids.push_back(asteroid);
}

void AsteroidManager::createAsteroidFragments(int scale, const Vector &position, const Vector &velocity) {
    if (scale == 1) {
        return;
    }

    std::uniform_int_distribution<> numFragmentsDist(2, 3);
    auto numFragments = numFragmentsDist(rng);

    for (int i = 0; i < numFragments; ++i) {
        auto asteroid = Asteroid(scale - 1, rng);

        asteroid.position = position;
        asteroid.velocity = velocity.normalized();

        std::uniform_real_distribution<float> speedDist(-1.5, 1.5);
        asteroid.velocity += Vector(speedDist(rng), speedDist(rng));
        asteroid.velocity.normalize();
        asteroid.velocity *= 200.0f / std::sqrt(static_cast<float>(scale));

        asteroid.angularVelocity = std::max(std::min(speedDist(rng), 2.0f), -2.0f);

        asteroids.push_back(asteroid);
    }
}





