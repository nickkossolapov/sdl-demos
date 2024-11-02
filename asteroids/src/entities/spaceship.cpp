#include <cmath>

#include "./spaceship.h"

#include <iostream>

#include "../globals.h"
#include "../config/colors.h"

Spaceship::Spaceship(float mass, float inertia) : Body2d(mass, inertia) {
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
            case SDLK_DOWN:
                isBreaking = true;
                break;
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
            case SDLK_DOWN:
                isBreaking = false;
                break;
            default:
                break;
        }
    }
}

void Spaceship::draw() const {
    auto [x, y, _] = position;

    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    float tipX = x + std::sin(orientation) * 30;
    float tipY = y + std::cos(orientation) * 30;

    constexpr float finAngle = 2.356194f; // 135 degrees

    float rearLeftX = x + std::sin(orientation - finAngle) * 20;
    float rearLeftY = y + std::cos(orientation - finAngle) * 20;

    float rearRightX = x + std::sin(orientation + finAngle) * 20;
    float rearRightY = y + std::cos(orientation + finAngle) * 20;

    SDL_RenderDrawLineF(gRenderer, x, y, tipX, tipY);
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(gRenderer, x, y, rearLeftX, rearLeftY);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xFF);
    SDL_RenderDrawLineF(gRenderer, x, y, rearRightX, rearRightY);
}

void Spaceship::update() {
    if (isThrusting) {
        constexpr float thrust = 500;

        netForce.x = std::sin(orientation) * thrust;
        netForce.y = std::cos(orientation) * thrust;
    } else {
        netForce.x = 0;
        netForce.y = 0;
    }

    if (isBreaking) {
        if (velocity.length() < 30) {
            velocity.x = 0;
            velocity.y = 0;
        } else {
            constexpr float breakingFactor = 1.05;

            velocity.x /= breakingFactor;
            velocity.y /= breakingFactor;
        }
    }
}

