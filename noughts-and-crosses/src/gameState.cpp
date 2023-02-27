#include "gameState.h"
#include "constants.h"

GameState::GameState(std::array<Tile, GRID_SIZE> &tiles) : mTiles(tiles) {
    mCurrentPlayer = PlayState::Cross;
    mOutcome = InProgress;
    mIsFilled = {};
}

void GameState::handleEvent(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONUP) {
        for (int i = 0; i < GRID_SIZE; ++i) {
            if (!mIsFilled[i] && mTiles[i].state() == Selected){
                mCurrentPlayer = mCurrentPlayer == Cross ? Nought : Cross;
                mIsFilled[i] = true;
            }
        }
    }
}

Outcome& GameState::outcome() {
    return mOutcome;
}

PlayState& GameState::currentPlayer() {
    return mCurrentPlayer;
}
