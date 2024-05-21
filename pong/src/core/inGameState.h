#ifndef PONG_INGAMESTATE_H
#define PONG_INGAMESTATE_H

#include <array>
#include "../game/paddle.h"
#include "../game/ball.h"
#include "gameState.h"
#include "score.h"
#include "../game/player.h"
#include "../ui/scoreUi.h"
#include "../game/cpuPlayer.h"

class InGameState : public GameState {
public:
    InGameState(ScoreUi &scoreUi);

    void handleEvent(SDL_Event &e) override;

    void update() override;

    void render(SDL_Renderer *renderer) override;

private:
    std::array<Paddle, 2> mPaddles;
    Player mPlayer;
    CpuPlayer mCpuPlayer;
    ScoreUi mScoreUi;
    Ball mBall;
    Score mScore;
    bool mPaused;

    void resetPositions();
};

#endif //PONG_INGAMESTATE_H
