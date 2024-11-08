#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <SDL.h>
#include "body2d.h"
#include "../managers/bulletManager.h"

class Spaceship final : public Body2d {
public:
    explicit Spaceship(float mass, float inertia, BulletManager &_bulletManager);

    void handleEvent(const SDL_Event &e);

    void draw() const override;

    void update() override;

private:
    float tipLength = 25;
    float wingLength = 15;

    int flameAnimationCount = 0;

    BulletManager &bulletManager;
    bool isThrusting = false;
    bool isTiltTrusting = false;

    void shoot();
};

#endif //ASTEROIDS_PLAYER_H
