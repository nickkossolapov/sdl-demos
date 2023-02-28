#ifndef NOUGHTS_AND_CROSSES_GAMEOVER_H
#define NOUGHTS_AND_CROSSES_GAMEOVER_H

#include <array>
#include "tile.h"
#include "gameState.h"

class GameOver {
public:
    GameOver(std::array<Tile, 9> &tiles);
    void setOutcome(Outcome outcome, std::optional<WinningLines> winningLines);
    void reset();
    void render(SDL_Renderer *renderer);

private:
    Outcome mOutcome;
    std::array<Tile, GRID_SIZE> &mTiles;
    std::optional<WinningLines> mWinningLines;
    bool mHasDisabledTiles;

    void disableTiles(std::array<int, 6> indicesToDisable);
};

#endif //NOUGHTS_AND_CROSSES_GAMEOVER_H
