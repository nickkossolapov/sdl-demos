#include <SDL.h>
#include "../game/paddle.h"
#include "../game/ball.h"
#include "inGameState.h"
#include "../config/constants.h"
#include "../config/colors.h"


InGameState::InGameState(SDL_Renderer *renderer, TTF_Font *font)
        : mScoreUi(font, renderer),
          mBall({10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20}),
          mPaddles{Paddle({PADDING, PADDING, Paddle::PADDLE_WIDTH, SCREEN_HEIGHT - 2 * PADDING}),
                   Paddle({SCREEN_WIDTH - PADDING - Paddle::PADDLE_WIDTH, PADDING, Paddle::PADDLE_WIDTH,
                           SCREEN_HEIGHT - 2 * PADDING})},
          mPlayer(mPaddles[0]),
          mCpuPlayer(mPaddles[1], mBall),
          mScore({0, 0}),
          mPaused(true),
          mGameOver(false),
          mWinnerText(TextTexture(font)),
          mRenderer(renderer) {}

void InGameState::handleEvent(SDL_Event &e) {
    if (mGameOver) {
        if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_KEYUP) {
            reset();
        }
    } else if (mPaused) {
        if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_KEYUP) {
            mBall.startBall();
            mPaused = false;
        }
    } else {
        mPlayer.handleEvent(e);
    }
}

void InGameState::checkGameOver() {
    if (mScore.player1 == WINNING_SCORE || mScore.player2 == WINNING_SCORE) {
        mWinnerText.setText(mRenderer, mScore.player1 > mScore.player2 ? "Player wins!" : "CPU wins!", OFF_WHITE,
                            OFF_BLACK);

        mPaused = true;
        mGameOver = true;
    }
}

void InGameState::update() {
    if (mBall.isOut()) {
        if (mBall.getPosition().x > SCREEN_WIDTH / 2) {
            mScore.player1 += 1;
        } else {
            mScore.player2 += 1;
        }

        checkGameOver();

        if (!mGameOver) {
            mScoreUi.setScore(mScore);
            resetPositions();
        }
    } else {
        mCpuPlayer.update();
        mBall.move(mPaddles);

        for (auto &paddle: mPaddles) {
            paddle.move();
        }
    }
}

void InGameState::render(SDL_Renderer *renderer) {
    if (mGameOver) {
        mWinnerText.render(renderer, {SCREEN_WIDTH / 2 - mWinnerText.getWidth() / 2,
                                      SCREEN_HEIGHT / 2 - mWinnerText.getHeight() / 2});
    } else {
        mBall.render(renderer);
        mScoreUi.render(renderer);
    }

    for (auto &paddle: mPaddles) {
        paddle.render(renderer);
    }
}

void InGameState::reset() {
    mScore = {0, 0};
    mScoreUi.setScore(mScore);
    resetPositions();
    mGameOver = false;
}

void InGameState::resetPositions() {
    mBall.reset();

    for (auto &paddle: mPaddles) {
        paddle.reset();
    }

    mPaused = true;
}
