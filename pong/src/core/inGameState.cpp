#include <SDL.h>
#include "../game/paddle.h"
#include "../game/ball.h"
#include "inGameState.h"
#include "../config/constants.h"


InGameState::InGameState(SDL_Renderer *renderer, TTF_Font *font)
        : mScoreUi(font, renderer),
          mBall({10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20}),
          mPaddles{Paddle({PADDING, PADDING, Paddle::PADDLE_WIDTH, SCREEN_HEIGHT - 2 * PADDING}),
                   Paddle({SCREEN_WIDTH - PADDING - Paddle::PADDLE_WIDTH, PADDING, Paddle::PADDLE_WIDTH,
                           SCREEN_HEIGHT - 2 * PADDING})},
          mPlayer(mPaddles[0]),
          mCpuPlayer(mPaddles[1], mBall),
          mScore({0, 0}),
          mPaused(true) {}

void InGameState::handleEvent(SDL_Event &e) {
    if (mPaused) {
        if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_KEYUP) {
            mBall.startBall();
            mPaused = false;
        }
    } else {
        mPlayer.handleEvent(e);
    }
}

void InGameState::update() {
    if (mBall.isOut()) {
        if (mBall.getPosition().y < SCREEN_WIDTH / 2) {
            mScore.player1 += 1;
        } else {
            mScore.player2 += 1;
        }

        mScoreUi.setScore(mScore);
        resetPositions();
    }

    mCpuPlayer.update();
    mBall.move(mPaddles);

    for (auto &paddle: mPaddles) {
        paddle.move();
    }
}

void InGameState::render(SDL_Renderer *renderer) {
    for (auto &paddle: mPaddles) {
        paddle.render(renderer);
    }

    mBall.render(renderer);
    mScoreUi.render(renderer);
}

void InGameState::resetPositions() {
    mBall.reset();

    for (auto &paddle: mPaddles) {
        paddle.reset();
    }

    mPaused = true;
}
