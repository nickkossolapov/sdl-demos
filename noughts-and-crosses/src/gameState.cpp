#include "gameState.h"
#include "constants.h"

GameState::GameState(std::array<Tile, GRID_SIZE> &tiles) : mTiles(tiles) {
    mCurrentPlayer = PlayState::Cross;
    mOutcome = InProgress;
    mCurrentBoard = {};
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
    if (e.type == SDL_MOUSEBUTTONUP) {
        for (int i = 0; i < GRID_SIZE; ++i) {
            if (!mCurrentBoard[i] && mTiles[i].state() == Selected) {
                mCurrentBoard[i] = mCurrentPlayer == Cross ? tCross : tNought;

                if (tryGetWinningLine().has_value()) {
                    mOutcome =  mCurrentPlayer == Cross ? NoughtWin : CrossWin;
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

std::optional<WinningLines> GameState::tryGetWinningLine() {
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
}
