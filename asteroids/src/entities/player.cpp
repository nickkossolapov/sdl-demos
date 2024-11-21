#include <cmath>
#include <iostream>

#include "./player.h"

#include "../globals.h"
#include "../config/colors.h"
#include "../config/config.h"
#include "../utils/controller.h"
#include "../constants.h"

Player::Player(float mass, float inertia, BulletManager &_bulletManager)
        : Body2d(mass, inertia), bulletManager(_bulletManager) {
    maxSpeed = 400;
    orientation = Constants::Pi;
}


void Player::handleEvent(const SDL_Event &e) {
    constexpr float turningSpeed = 5;

    if (e.type == SDL_JOYAXISMOTION) {
        if (e.jaxis.which == 0 && e.jaxis.axis == 0) {
            angularVelocity = -getAxisTilt(e.jaxis.value) * turningSpeed;
        }
        if (e.jaxis.which == 0 && e.jaxis.axis == 1) {
            if (fabsf(getAxisTilt(e.jaxis.value)) > 0.7) {
                isTiltTrusting = true;
            } else {
                isTiltTrusting = false;
            }
        }
    } else if (e.type == SDL_JOYBUTTONDOWN) {
        switch (e.jbutton.button) {
            case 0:
                isThrusting = true;
                break;
            case 2:
                shoot();
                break;
            default:
                break;
        }
    } else if (e.type == SDL_JOYBUTTONUP) {
        switch (e.jbutton.button) {
            case 0:
                isThrusting = false;
                break;
            default:
                break;
        }
    } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                angularVelocity += turningSpeed;
                break;
            case SDLK_LEFT:
                angularVelocity += -turningSpeed;
                break;
            case SDLK_UP:
                isThrusting = true;
                break;
            case SDLK_SPACE:
            case SDLK_TAB:
                shoot();
            default:
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                angularVelocity -= turningSpeed;
                break;
            case SDLK_LEFT:
                angularVelocity -= -turningSpeed;
                break;
            case SDLK_UP:
                isThrusting = false;
                break;
            default:
                break;
        }
    }
}

void Player::draw() const {
    auto [r, g, b, a] = Colours::white;

    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    auto [x, y, _] = position;
    auto [tip, leftWing, rightWing, leftThruster, rightThruster] = edges;

    SDL_RenderDrawLineF(gRenderer, tip.x, tip.y, leftWing.x, leftWing.y);
    SDL_RenderDrawLineF(gRenderer, tip.x, tip.y, rightWing.x, rightWing.y);
    SDL_RenderDrawLineF(gRenderer, rightThruster.x, rightThruster.y, rightWing.x, rightWing.y);
    SDL_RenderDrawLineF(gRenderer, leftThruster.x, leftThruster.y, leftWing.x, leftWing.y);
    SDL_RenderDrawLineF(gRenderer, leftThruster.x, leftThruster.y, rightThruster.x, rightThruster.y);

    if (isThrusting || isTiltTrusting) {
        if (SDL_GetTicks() % 2 == 0) {
            float flameEndX = x - std::sin(orientation) * wingLength;
            float flameEndY = y - std::cos(orientation) * wingLength;
            auto foo = position - Vector{flameEndX, flameEndY};
            std::cout << foo.length() << std::endl;

            SDL_RenderDrawLineF(gRenderer, leftThruster.x, leftThruster.y, flameEndX, flameEndY);
            SDL_RenderDrawLineF(gRenderer, rightThruster.x, rightThruster.y, flameEndX, flameEndY);
        }
    }
}

void Player::updateEdges() {
    auto [x, y, _] = position;

    edges.tip.x = x + std::sin(orientation) * tipLength;
    edges.tip.y = y + std::cos(orientation) * tipLength;

    constexpr float finAngle = 2.356194f; // 135 degrees

    edges.leftThruster.x = x + std::sin(orientation - finAngle) * wingLength / 2;
    edges.leftThruster.y = y + std::cos(orientation - finAngle) * wingLength / 2;
    edges.leftWing.x = x + std::sin(orientation - finAngle) * wingLength;
    edges.leftWing.y = y + std::cos(orientation - finAngle) * wingLength;

    edges.rightThruster.x = x + std::sin(orientation + finAngle) * wingLength / 2;
    edges.rightThruster.y = y + std::cos(orientation + finAngle) * wingLength / 2;
    edges.rightWing.x = x + std::sin(orientation + finAngle) * wingLength;
    edges.rightWing.y = y + std::cos(orientation + finAngle) * wingLength;
}

void Player::update() {
    if (isThrusting || isTiltTrusting) {
        constexpr float thrust = 500;

        netForce.x = std::sin(orientation) * thrust;
        netForce.y = std::cos(orientation) * thrust;
    } else {
        netForce.x = 0;
        netForce.y = 0;

        if (velocity.length() < 30) {
            velocity.x = 0;
            velocity.y = 0;
        } else {
            constexpr float breakingFactor = 1.01;

            velocity.x /= breakingFactor;
            velocity.y /= breakingFactor;
        }
    }

    if (position.x < 0) {
        position.x = ScreenSize::width;
    } else if (position.x > ScreenSize::width) {
        position.x = 0;
    }

    if (position.y < 0) {
        position.y = ScreenSize::height;
    } else if (position.y > ScreenSize::height) {
        position.y = 0;
    }
}

void Player::shoot() {
    auto [x, y, z] = position;
    float tipX = x + std::sin(orientation) * tipLength;
    float tipY = y + std::cos(orientation) * tipLength;

    auto bullet = Bullet({tipX, tipY}, {std::sin(orientation), std::cos(orientation)});

    bulletManager.addBullet(bullet);
}

void Player::reset() {
    position = {ScreenSize::width / 2.0f, ScreenSize::height / 2.0f};
    velocity = {0, 0};
    orientation = Constants::Pi;
    angularVelocity = 0;
    hasCollided = false;
    isThrusting = false;
    isTiltTrusting = false;
}
