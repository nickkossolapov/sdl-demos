#include <cmath>
#include "paddle.h"
#include "../config/constants.h"
#include "../config/colors.h"

Paddle::Paddle(const SDL_Rect playBoundary) {
    mPaddleRect = {
            playBoundary.x,
            playBoundary.h / 2 - PADDLE_HEIGHT / 2,
            PADDLE_WIDTH,
            PADDLE_HEIGHT
    };

    mBoundingRect = playBoundary;
    mVelY = 0;
}

void Paddle::setVelocity(const float velocity) {
    mVelY = velocity > 0
            ? std::min(velocity, MAX_VELOCITY)
            : std::max(velocity, -MAX_VELOCITY);
}

void Paddle::move() {
    mPaddleRect.y += std::lround(mVelY);

    if (mPaddleRect.y < mBoundingRect.y) {
        mPaddleRect.y = mBoundingRect.y;
        mVelY = 0;
    }

    if (mPaddleRect.y + mPaddleRect.h > mBoundingRect.y + mBoundingRect.h) {
        mPaddleRect.y = +mBoundingRect.y + mBoundingRect.h - mPaddleRect.h;
        mVelY = 0;
    }
}

void Paddle::render(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE.r, OFF_WHITE.g, OFF_WHITE.b, 0xFF);
    SDL_RenderFillRect(renderer, &mPaddleRect);
}

void Paddle::reset() {
    mPaddleRect = {
            mBoundingRect.x,
            mBoundingRect.h / 2 - PADDLE_HEIGHT / 2,
            PADDLE_WIDTH,
            PADDLE_HEIGHT
    };

    mVelY = 0;
}

SDL_Rect &Paddle::getCollisionBox() {
    return mPaddleRect;
}
