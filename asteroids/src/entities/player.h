#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <SDL.h>
#include "body2d.h"
#include "../managers/bulletManager.h"

struct PlayerEdges {
    Vector tip;
    Vector leftWing;
    Vector rightWing;
    Vector leftThruster;
    Vector rightThruster;
};

class Player final : public Body2d {
public:
    bool isInvincible = false;
    bool hasCollided = false;

    explicit Player(float mass, float inertia, BulletManager &_bulletManager);

    void handleEvent(const SDL_Event &e);

    void draw() const override;

    void update() override;

    void updateEdges();

    float getLongestSide() const {
        return tipLength;
    }

    PlayerEdges &getEdges() {
        return edges;
    }

    void reset();

private:
    float tipLength = 25;
    float wingLength = 15;
    BulletManager &bulletManager;
    bool isThrusting = false;
    bool isTiltTrusting = false;

    PlayerEdges edges;

    void shoot();
};

#endif //ASTEROIDS_PLAYER_H
