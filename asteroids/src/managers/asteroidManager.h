#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include <random>

#include "bulletManager.h"
#include "../entities/asteroid.h"

class AsteroidManager {
public:
    explicit AsteroidManager(int initialAsteroids, BulletManager &_bulletManager);

    void update();

    void updateBodiesEuler(float dt);

    void drawAsteroids() const;

private:
    BulletManager &bulletManager;
    std::vector<Asteroid> asteroids;
    std::mt19937 rng;

    void createAsteroid();

    void createAsteroidFragments(int scale, const Vector &position, const Vector &velocity);
};

#endif //ASTEROIDMANAGER_H
