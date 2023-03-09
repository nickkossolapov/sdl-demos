#include <cmath>
#include <array>
#include "ball.h"
#include "constants.h"
#include "colors.h"

Ball::Ball(SDL_Rect playBoundary) {
    mBallRect = {
            SCREEN_HEIGHT / 2 - BALL_HEIGHT / 2,
            SCREEN_WIDTH / 2 - BALL_HEIGHT / 2,
            BALL_WIDTH,
            BALL_HEIGHT
    };

    mBoundingRect = playBoundary;
    mVelX = -INITIAL_SPEED;
    mVelY = -INITIAL_SPEED * (0.5f - (float) rand() / RAND_MAX); // NOLINT(cert-msc50-cpp)
    mOut = false;
    mCollidingWithPaddle = false;
    mServed = false;
}

void Ball::move(std::vector<Paddle> &paddles) {
    if (mOut) {
        return;
    }

    mBallRect.x += (int) roundf(mVelX);
    mBallRect.y += (int) roundf(mVelY);

    for (auto &paddle: paddles) {
        if (SDL_HasIntersection(&mBallRect, &(paddle.getCollisionBox()))) {
            if (!mServed) {
                mServed = true;
                mVelX *= SPEED_MULTIPLIER;
                mVelY *= SPEED_MULTIPLIER;
            }

            if (!mCollidingWithPaddle) {
                mVelX = -mVelX;
                mVelY += BALL_DISPERSION * (0.5f - (float) rand() / RAND_MAX); // NOLINT(cert-msc50-cpp)
                mCollidingWithPaddle = true;
            }
        } else {
            mCollidingWithPaddle = false;
        }
    }

    if ((mBallRect.x < mBoundingRect.x) || (mBallRect.x + mBallRect.w > mBoundingRect.x + mBoundingRect.w)) {
        mVelX = 0;
        mVelY = 0;
        mOut = true;
    }


    if ((mBallRect.y < mBoundingRect.y) || (mBallRect.y + mBallRect.h > mBoundingRect.y + mBoundingRect.h)) {
        mBallRect.y -= (int) roundf(mVelY);
        mVelY = -mVelY;
    }
}

SDL_Point Ball::getCenter() const {
    return {mBallRect.x + mBallRect.w / 2, mBallRect.y + mBallRect.h / 2};
}

std::pair<float, float> Ball::getVelocity() const {
    return {mVelX, mVelY};
}

void Ball::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE.r, OFF_WHITE.g, OFF_WHITE.b, 0xFF);
    SDL_RenderFillRect(renderer, &mBallRect);
}

void Ball::reset() {
    mBallRect.x = SCREEN_HEIGHT / 2 - BALL_HEIGHT / 2;
    mBallRect.y = SCREEN_WIDTH / 2 - BALL_HEIGHT / 2;
    mVelX = -INITIAL_SPEED;
    mVelY = -INITIAL_SPEED * (0.5f - (float) rand() / RAND_MAX); // NOLINT(cert-msc50-cpp)
    mOut = false;
    mCollidingWithPaddle = false;
    mServed = false;
}
