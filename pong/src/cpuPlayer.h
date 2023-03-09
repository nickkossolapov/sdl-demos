#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include "paddle.h"
#include "ball.h"
#include "constants.h"

class CpuPlayer {
public:
    CpuPlayer(Paddle &paddle, Ball &ball);

    void movePaddle();

private:
    const float MAX_VELOCITY = 20;
    const float ACCELERATION = 2;
    const float DECELERATION = 1.075;

    Paddle &mPaddle;
    Ball &mBall;
    float mCurrentVelocity;
};

#endif //CPUPLAYER_H
