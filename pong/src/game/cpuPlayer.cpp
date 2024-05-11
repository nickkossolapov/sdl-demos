#include "cpuPlayer.h"

CpuPlayer::CpuPlayer(Paddle &paddle, Ball &ball) : mPaddle(paddle), mBall(ball) {
    mCurrentVelocity = 0;
}

void CpuPlayer::movePaddle() {
    if (mBall.isOut()) {
        mCurrentVelocity = 0;
        return;
    }

    const SDL_Point ballCenter = mBall.getCenter();
    auto [ballVel, _] = mBall.getVelocity();
    const SDL_Rect paddleRect = mPaddle.getCollisionBox();

    if (ballVel < 0) {
        mCurrentVelocity = 0;
    } else {
        if (ballCenter.y > (paddleRect.y + paddleRect.h)) {
            mCurrentVelocity = std::min(mCurrentVelocity + ACCELERATION, MAX_VELOCITY);
            mPaddle.setVelocity(mCurrentVelocity);
        } else if (ballCenter.y < paddleRect.y) {
            mCurrentVelocity = std::max(mCurrentVelocity - ACCELERATION, -MAX_VELOCITY);
            mPaddle.setVelocity(mCurrentVelocity);
        } else {
            mCurrentVelocity /= DECELERATION;
        }
    }

    mPaddle.setVelocity(mCurrentVelocity);
}
