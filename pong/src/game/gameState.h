#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "paddle.h"
#include "ball.h"
#include "score.h"

class GameState {
public:
    GameState(std::array<Paddle, 2> &paddles, Ball &ball);

    void handleEvent(SDL_Event &e);

    void checkCurrentState();

    Score getScore() const;

private:
    std::array<Paddle, 2> &mPaddles;
    Ball &mBall;
    Score mScore;
    bool mPaused;

    void resetPositions();
};

#endif //GAMESTATE_H
