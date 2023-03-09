#include "cpuPlayer.h"

CpuPlayer::CpuPlayer(Paddle &paddle, Ball &ball) : mPaddle(paddle), mBall(ball) {
    mCurrentVelocity = 0;
}

void CpuPlayer::movePaddle() {
    SDL_Point ballCenter = mBall.getCenter();
    auto [ballXVel, _] = mBall.getVelocity();
    SDL_Rect paddleRect = mPaddle.getCollisionBox();

    if (ballXVel < 0) {
        mCurrentVelocity = 0;
    } else {
        if (ballCenter.y > (paddleRect.y + paddleRect.h)) {
            mCurrentVelocity = std::min(mCurrentVelocity + ACCELERATION, (float) MAX_VELOCITY);
            mPaddle.setVelocity(mCurrentVelocity);
        } else if (ballCenter.y < paddleRect.y) {
            mCurrentVelocity = std::max(mCurrentVelocity - ACCELERATION, (float) -MAX_VELOCITY);
            mPaddle.setVelocity(mCurrentVelocity);
        } else {
            mCurrentVelocity /= DECELERATION;
        }
    }

    mPaddle.setVelocity(mCurrentVelocity);
}
