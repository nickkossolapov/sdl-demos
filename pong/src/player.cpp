#include "player.h"
#include "constants.h"

Player::Player(Paddle &paddle) : mPaddle(paddle) {}

void Player::handleEvent(SDL_Event &e) {
    if (e.type == SDL_JOYAXISMOTION) {
        if (e.jaxis.which == 0 && e.jaxis.axis == 1) {
            if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
                mPaddle.setVelocity((float) e.jaxis.value * JOYSTICK_MAX_LIMIT);
            } else {
                mPaddle.setVelocity(0);
            }
        }
    }

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mPaddle.setVelocity(-Paddle::MAX_VELOCITY);
                break;
            case SDLK_DOWN:
                mPaddle.setVelocity(Paddle::MAX_VELOCITY);
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                mPaddle.setVelocity(0);
                break;
        }
    }
}

