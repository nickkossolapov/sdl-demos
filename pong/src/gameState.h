#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "paddle.h"
#include "ball.h"
#include "score.h"

class GameState {
public:
    GameState(std::vector<Paddle> &paddles, Ball &ball);

    void handleEvent(SDL_Event &e);

    void checkCurrentState();

private:
    std::vector<Paddle> &mPaddles;
    Ball &mBall;
    Score mScore;
    bool mPaused;

    void resetPositions();
};

#endif //GAMESTATE_H
