#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include <random>

#include "bulletManager.h"
#include "score.h"
#include "../entities/asteroid.h"
#include "../entities/player.h"

class AsteroidManager {
public:
    explicit AsteroidManager(int initialAsteroids, BulletManager& _bulletManager, Score& _score, Player& player);

    void update();

    void updateBodiesEuler(float dt);

    void drawAsteroids() const;

    void reset();

private:
    BulletManager& bulletManager;
    Score& score;
    Player& player;
    std::vector<Asteroid> asteroids;
    std::mt19937 rng;
    int initialAsteroids;

    void createAsteroid();

    void createAsteroidFragments(int scale, const Vector& position, const Vector& velocity);

    void checkCollisionWithPlayer(Asteroid& asteroid);
};

#endif //ASTEROIDMANAGER_H
