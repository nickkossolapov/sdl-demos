#include <cmath>

#include "./spaceship.h"

#include <iostream>

#include "../globals.h"
#include "../config/colors.h"
#include "../config/config.h"

Spaceship::Spaceship(float mass, float inertia, BulletManager &_bulletManager)
    : Body2d(mass, inertia), bulletManager(_bulletManager) {
    maxSpeed = 400;
}


void Spaceship::handleEvent(const SDL_Event &e) {
    constexpr float turningSpeed = 4;

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
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

void Spaceship::draw() const {
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    auto [x, y, _] = position;

    float tipX = x + std::sin(orientation) * tipLength;
    float tipY = y + std::cos(orientation) * tipLength;

    float rearX = x - std::sin(orientation) * 5;
    float rearY = y - std::cos(orientation) * 5;

    constexpr float finAngle = 2.356194f; // 135 degrees

    float leftWingX = x + std::sin(orientation - finAngle) * wingLength;
    float leftWingY = y + std::cos(orientation - finAngle) * wingLength;

    float rightWingX = x + std::sin(orientation + finAngle) * wingLength;
    float rightWingY = y + std::cos(orientation + finAngle) * wingLength;

    SDL_RenderDrawLineF(gRenderer, tipX, tipY, leftWingX, leftWingY);
    SDL_RenderDrawLineF(gRenderer, tipX, tipY, rightWingX, rightWingY);
    SDL_RenderDrawLineF(gRenderer, rearX, rearY, rightWingX, rightWingY);
    SDL_RenderDrawLineF(gRenderer, rearX, rearY, leftWingX, leftWingY);
}

void Spaceship::update() {
    if (isThrusting) {
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

void Spaceship::shoot() {
    auto [x, y, z] = position;
    float tipX = x + std::sin(orientation) * tipLength;
    float tipY = y + std::cos(orientation) * tipLength;

    auto bullet = Bullet({tipX, tipY}, {std::sin(orientation), std::cos(orientation)});

    bulletManager.addBullet(bullet);
}
