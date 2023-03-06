#include <cmath>
#include "paddle.h"
#include "constants.h"
#include "colors.h"

Paddle::Paddle(SDL_Rect playBoundary) {
    mPaddleRect = {
            SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
            PLAY_AREA_PADDING,
            PADDLE_WIDTH,
            PADDLE_HEIGHT
    };

    mBoundingRect = playBoundary;
    mVelX = 0;
    mVelY = 0;
}

void Paddle::handleEvent(SDL_Event &e) {
    if (e.type == SDL_JOYAXISMOTION) {
        if (e.jaxis.which == 0) {
            if (e.jaxis.axis == 0) {
                if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
                    mVelX = (float) e.jaxis.value * JOYSTICK_MAX_LIMIT;
                } else {
                    mVelX = 0;
                }
            } else if (e.jaxis.axis == 1) {
                if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
                    mVelY = (float) e.jaxis.value * JOYSTICK_MAX_LIMIT;
                } else {
                    mVelY = 0;
                }
            }
        }
    }

    if (e.type == SDL_KEYDOWN) {
        //todo improve keyboard input
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY = fmaxf(mVelY - 4, -MAX_VELOCITY);
                break;
            case SDLK_DOWN:
                mVelY = fminf(mVelY + 4, MAX_VELOCITY);
                break;
            case SDLK_LEFT:
                mVelX = fmaxf(mVelX - 4, -MAX_VELOCITY);
                break;
            case SDLK_RIGHT:
                mVelX = fminf(mVelX + 4, MAX_VELOCITY);
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                mVelX = 0;
                break;
        }
    }
}

void Paddle::move() {
    mPaddleRect.x += (int) roundf(mVelX);
    if ((mPaddleRect.x < mBoundingRect.x) || (mPaddleRect.x + mPaddleRect.w > mBoundingRect.x + mBoundingRect.w)) {
        mPaddleRect.x -= (int) roundf(mVelX);
    }

    mPaddleRect.y += (int) roundf(mVelY);
    if ((mPaddleRect.y < mBoundingRect.y) || (mPaddleRect.y + mPaddleRect.h > mBoundingRect.y + mBoundingRect.h)) {
        mPaddleRect.y -= (int) roundf(mVelY);
    }
}

void Paddle::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE.r, OFF_WHITE.g, OFF_WHITE.b, 0xFF);
    SDL_RenderFillRect(renderer, &mPaddleRect);
}

SDL_Rect &Paddle::getCollisionBox() {
    return mPaddleRect;
}
