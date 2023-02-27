#ifndef NOUGHTS_AND_CROSSES_GAMESTATE_H
#define NOUGHTS_AND_CROSSES_GAMESTATE_H

#include <array>
#include "states.h"
#include "tile.h"
#include "constants.h"

enum Outcome {
    InProgress,
    NoughtWin,
    CrossWin,
    Draw
};

class GameState {
public:
    GameState(std::array<Tile, 9> &tiles);
    PlayState& currentPlayer();
    Outcome& outcome();
    void handleEvent(SDL_Event &e);

private:
    PlayState mCurrentPlayer;
    Outcome mOutcome;
    std::array<Tile, GRID_SIZE>& mTiles;
    std::array<bool, GRID_SIZE> mIsFilled;
};

#endif //NOUGHTS_AND_CROSSES_GAMESTATE_H
