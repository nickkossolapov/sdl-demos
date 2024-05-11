#include <array>
#include "gameState.h"
#include "../config/constants.h"

GameState::GameState(std::array<Paddle, 2> &paddles, Ball &ball)
    : mPaddles(paddles),
      mBall(ball),
      mScore({0, 0}),
      mPaused(true) {
}

void GameState::handleEvent(SDL_Event &e) {
    if (mPaused) {
        if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_KEYUP) {
            mBall.startBall();
            mPaused = false;
        }
    }
}

void GameState::checkCurrentState() {
    if (mBall.isOut()) {
        if (mBall.getPosition().y < SCREEN_WIDTH / 2) {
            mScore.player1 += 1;
        } else {
            mScore.player2 += 1;
        }

        resetPositions();
    }
}

void GameState::resetPositions() {
    mBall.reset();

    for (auto &paddle: mPaddles) {
        paddle.reset();
    }

    mPaused = true;
}

Score GameState::getScore() const {
    return mScore;
}
