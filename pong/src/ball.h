#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <vector>
#include "paddle.h"

class Ball {
public:
    Ball(SDL_Rect playBoundary);

    void move(std::vector<Paddle> &paddles);

    SDL_Point getCenter() const;

    std::pair<float, float> getVelocity() const;

    void render(SDL_Renderer *renderer);

    void reset();

private:
    static const int BALL_HEIGHT = 20;
    static const int BALL_WIDTH = 20;
    static const int SPEED_MULTIPLIER = 4;
    const float INITIAL_SPEED = 3;
    const float BALL_DISPERSION = 7;

    SDL_Rect mBoundingRect{};
    SDL_Rect mBallRect{};
    float mVelX, mVelY;
    bool mOut;
    bool mServed;
    bool mCollidingWithPaddle; // needed when ball collides with top/bottom of panel, or it gets stuck in the paddle
};

#endif //BALL_H
