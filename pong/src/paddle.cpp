#include <cmath>
#include "paddle.h"
#include "constants.h"
#include "colors.h"

Paddle::Paddle(SDL_Rect playBoundary) {
    mPaddleRect = {
            playBoundary.x,
            playBoundary.h / 2 - PADDLE_HEIGHT / 2,
            PADDLE_WIDTH,
            PADDLE_HEIGHT
    };

    mBoundingRect = playBoundary;
    mVelY = 0;
}

void Paddle::handleEvent(SDL_Event &e) {
    if (e.type == SDL_JOYAXISMOTION) {
        if (e.jaxis.which == 0 && e.jaxis.axis == 1) {
            if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
                mVelY = (float) e.jaxis.value * JOYSTICK_MAX_LIMIT;
            } else {
                mVelY = 0;
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
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
        }
    }
}

void Paddle::move() {
    mPaddleRect.y += (int) roundf(mVelY);

    if (mPaddleRect.y < mBoundingRect.y) {
        mPaddleRect.y = mBoundingRect.y;
        mVelY = 0;

    }

    if (mPaddleRect.y + mPaddleRect.h > mBoundingRect.y + mBoundingRect.h) {
        mPaddleRect.y = + mBoundingRect.y + mBoundingRect.h - mPaddleRect.h;
        mVelY = 0;
    }
}

void Paddle::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE.r, OFF_WHITE.g, OFF_WHITE.b, 0xFF);
    SDL_RenderFillRect(renderer, &mPaddleRect);
}

SDL_Rect &Paddle::getCollisionBox() {
    return mPaddleRect;
}
