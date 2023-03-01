#ifndef NOUGHTS_AND_CROSSES_GAMESTATE_H
#define NOUGHTS_AND_CROSSES_GAMESTATE_H

#include <array>
#include "tile.h"
#include "constants.h"

enum Outcome {
    InProgress,
    NoughtWin,
    CrossWin,
    Draw
};

enum WinningLine {
    Row1,
    Row2,
    Row3,
    Column1,
    Column2,
    Column3,
    Diagonal,
    OffDiagonal
};

class GameState {
public:
    GameState(std::array<Tile, 9> &tiles);

    PlayState &currentPlayer();

    Outcome &outcome();

    void handleEvent(SDL_Event &e);

    void highlightWinningLine();

    void reset();

private:
    enum TileState {
        tEmpty = 0x00,
        tNought = 0x01,
        tCross = 0x02,
    };

    PlayState mCurrentPlayer;
    Outcome mOutcome;
    std::array<Tile, GRID_SIZE> &mTiles;
    std::array<TileState, GRID_SIZE> mCurrentBoard{};
    bool mHasDisabledTiles;

    bool isBoardFull();
    std::optional<WinningLine> tryGetWinningLine();
    void disableTiles(std::array<int, 6> indicesToDisable);
};

#endif //NOUGHTS_AND_CROSSES_GAMESTATE_H
