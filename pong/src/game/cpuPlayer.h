#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include "paddle.h"
#include "ball.h"

class CpuPlayer {
public:
    explicit CpuPlayer(Paddle &paddle, Ball &ball);

    void update();

private:
    const float MAX_VELOCITY = 20;
    const float ACCELERATION = 2.1;
    const float DECELERATION = 1.15;

    Paddle &mPaddle;
    Ball &mBall;
    float mCurrentVelocity;
};

#endif //CPUPLAYER_H
