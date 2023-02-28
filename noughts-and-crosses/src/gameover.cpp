#include <SDL.h>
#include "gameover.h"

GameOver::GameOver(std::array<Tile, GRID_SIZE> &tiles) : mTiles(tiles) {
    mOutcome = InProgress;
    mWinningLines = {};
    mHasDisabledTiles = false;
}

void GameOver::setOutcome(Outcome outcome, std::optional<WinningLines> winningLines) {
    mOutcome = outcome;
    mWinningLines = winningLines;
}

void GameOver::reset() {
    mOutcome = InProgress;
    mWinningLines = {};
    mHasDisabledTiles = false;
}

void GameOver::render(SDL_Renderer *renderer) {
    if (mOutcome == InProgress) {
        return;
    }

    if (mOutcome == Draw) {
        for (auto &tile: mTiles) {
            tile.disable();
        }
    }

    if (!mWinningLines.has_value()) {
        return;
    }

    if (!mHasDisabledTiles) {
        mHasDisabledTiles = true;

        /* Board ordering is
           0 3 6
           1 4 7
           2 5 8 */
        switch (mWinningLines.value()) {
            case Row1: {
                disableTiles({1, 2, 4, 5, 7, 8});
                break;
            }
            case Row2: {
                disableTiles({0, 2, 3, 5, 6, 8});
                break;
            }
            case Row3: {
                disableTiles({0, 1, 3, 4, 6, 7});
                break;
            }
            case Column1: {
                disableTiles({3, 4, 5, 6, 7, 8});
                break;
            }
            case Column2: {
                disableTiles({0, 1, 2, 6, 7, 8});
                break;
            }
            case Column3: {
                disableTiles({0, 1, 2, 3, 4, 5});
                break;
            }
            case Diagonal: {
                disableTiles({1, 2, 3, 5, 6, 7});

                break;
            }
            case OffDiagonal: {
                disableTiles({0, 1, 3, 5, 7, 8});
                break;

            }
        }
    }
}

void GameOver::disableTiles(std::array<int, 6> indicesToDisable) {
    for (int i: indicesToDisable) {
        mTiles[i].disable();
    }
}
