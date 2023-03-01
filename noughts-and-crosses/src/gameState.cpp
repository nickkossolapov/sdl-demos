#include "gameState.h"
#include "constants.h"

GameState::GameState(std::array<Tile, GRID_SIZE> &tiles) : mTiles(tiles) {
    mCurrentPlayer = PlayState::Cross;
    mOutcome = InProgress;
    mHasDisabledTiles = false;
}

bool GameState::isBoardFull() {
    for (auto state: mCurrentBoard) {
        if (state == tEmpty) {
            return false;
        }
    }

    return true;
}

void GameState::handleEvent(SDL_Event &e) {
    if (mOutcome != InProgress) {
        return;
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        for (int i = 0; i < GRID_SIZE; ++i) {
            if (!mCurrentBoard[i] && mTiles[i].state() == Selected) {
                mCurrentBoard[i] = mCurrentPlayer == Cross ? tCross : tNought;

                if (tryGetWinningLine().has_value()) {
                    mOutcome =  mCurrentPlayer == Cross ? CrossWin : NoughtWin;
                    return;
                } else if (isBoardFull()){
                    mOutcome = Draw;
                    return;
                }

                mCurrentPlayer = mCurrentPlayer == Cross ? Nought : Cross;
            }
        }
    }
}

Outcome &GameState::outcome() {
    return mOutcome;
}

PlayState &GameState::currentPlayer() {
    return mCurrentPlayer;
}

std::optional<WinningLine> GameState::tryGetWinningLine() {
    /* Board ordering is
       0 3 6
       1 4 7
       2 5 8 */
    if ((mCurrentBoard[0] & mCurrentBoard[3] & mCurrentBoard[6])) return Row1;
    if ((mCurrentBoard[1] & mCurrentBoard[4] & mCurrentBoard[7])) return Row2;
    if ((mCurrentBoard[2] & mCurrentBoard[5] & mCurrentBoard[8])) return Row3;
    if ((mCurrentBoard[0] & mCurrentBoard[1] & mCurrentBoard[2])) return Column1;
    if ((mCurrentBoard[3] & mCurrentBoard[4] & mCurrentBoard[5])) return Column2;
    if ((mCurrentBoard[6] & mCurrentBoard[7] & mCurrentBoard[8])) return Column3;
    if ((mCurrentBoard[0] & mCurrentBoard[4] & mCurrentBoard[8])) return Diagonal;
    if ((mCurrentBoard[2] & mCurrentBoard[4] & mCurrentBoard[6])) return OffDiagonal;
}

void GameState::reset() {
    mCurrentPlayer = PlayState::Cross;
    mOutcome = InProgress;
    mCurrentBoard = {};
    mHasDisabledTiles = false;
}

std::array<int, 6> getIndicesToDisable(WinningLine winningLine) {
    /* Board ordering is
     * 0 3 6
     * 1 4 7
     * 2 5 8 */
    switch (winningLine) {
        case Row1:
            return {1, 2, 4, 5, 7, 8};
        case Row2:
            return {0, 2, 3, 5, 6, 8};
        case Row3:
            return {0, 1, 3, 4, 6, 7};
        case Column1:
            return {3, 4, 5, 6, 7, 8};
        case Column2:
            return {0, 1, 2, 6, 7, 8};
        case Column3:
            return {0, 1, 2, 3, 4, 5};
        case Diagonal:
            return {1, 2, 3, 5, 6, 7};
        case OffDiagonal:
            return {0, 1, 3, 5, 7, 8};
    }
}

void GameState::highlightWinningLine() {
    if (mOutcome == InProgress) {
        return;
    }

    if (mOutcome == Draw) {
        for (auto &tile: mTiles) {
            tile.disable();
        }
    }

    auto winningLine = tryGetWinningLine();

    if (!winningLine.has_value()) {
        return;
    }

    if (!mHasDisabledTiles) {
        mHasDisabledTiles = true;
        disableTiles(getIndicesToDisable(winningLine.value()));
    }
}

void GameState::disableTiles(std::array<int, 6> indicesToDisable) {
    for (int i: indicesToDisable) {
        mTiles[i].disable();
    }
}
