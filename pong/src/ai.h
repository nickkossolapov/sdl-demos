#ifndef AI_H
#define AI_H

#include "paddle.h"
#include "ball.h"
#include "constants.h"

class Ai {
public:
    Ai(Paddle &paddle, Ball &ball);

    void movePaddle();

private:
    const float MAX_VELOCITY = 20;
    const float ACCELERATION = 2;
    const float DECELERATION = 1.075;

    Paddle &mPaddle;
    Ball &mBall;
    float mCurrentVelocity;
};

#endif //AI_H
