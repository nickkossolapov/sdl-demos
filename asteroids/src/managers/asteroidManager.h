#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include "bulletManager.h"
#include "../entities/asteroid.h"

class AsteroidManager {
public:
    explicit AsteroidManager(BulletManager &_bulletManager) : bulletManager(_bulletManager) {
        auto asteroid = Asteroid(1);

        asteroid.position = {200, 200};

        asteroids.push_back(asteroid);
    }

    void update();

    void updateBodiesEuler(float dt) const;

    void drawAsteroids() const;

private:
    BulletManager &bulletManager;
    std::vector<Asteroid> asteroids;
};

#endif //ASTEROIDMANAGER_H
