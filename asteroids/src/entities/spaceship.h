#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include <SDL.h>
#include "body2d.h"
#include "bulletManager.h"

class Spaceship : public Body2d {
public:
    explicit Spaceship(float mass, float inertia, BulletManager &_bulletManager);

    void handleEvent(const SDL_Event &e);

    void draw() const override;

    void update() override;

private:
    float tipLength = 25;
    float wingLength = 15;

    BulletManager &bulletManager;
    bool isThrusting = false;
    bool isBreaking = false;

    void shoot();
};

#endif //ASTEROIDS_SPACESHIP_H
