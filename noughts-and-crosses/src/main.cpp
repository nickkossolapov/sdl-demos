#include <string>
#include <SDL.h>
#include "colors.h"
#include "globals.h"
#include "shapeDrawer.h"
#include "utils.h"
#include "tileGenerator.h"
#include "gameState.h"
#include "textTexture.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE.r, OFF_WHITE.g, OFF_WHITE.b, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;
    SDL_Point gridOffset = {60, 60};

    auto tiles = generateTiles(GRID_LENGTH, TILE_SIZE, gridOffset);
    GameState gameState = {tiles};
    bool completed = false;

    TextTexture clickToContinueText = TextTexture(gFont);
    char clickToContinue[] = "Click to continue";
    clickToContinueText.setText(gRenderer, clickToContinue, OFF_BLACK);
    SDL_Point clickToContinueTopLeft = {
            gridOffset.x + GRID_LENGTH - clickToContinueText.getWidth(),
            gridOffset.y + GRID_LENGTH + TEXT_PADDING
    };
    TextTexture winnerText = TextTexture(gFont);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (gameState.outcome() == Outcome::InProgress) {
                for (auto &tile: tiles) {
                    tile.handleEvent(e, gameState.currentPlayer());
                }

                gameState.handleEvent(e);
            } else {
                if (e.type == SDL_MOUSEBUTTONUP) {
                    gameState.reset();
                    for (auto &tile: tiles) {
                        tile.reset();
                    }
                    winnerText.free();
                    completed = false;
                }

            }
        }

        prepareRenderer(gRenderer);

        if (gameState.outcome() != Outcome::InProgress) {
            if (!completed) {
                gameState.highlightWinningLine();

                std::string outcomeText;

                switch (gameState.outcome()) {
                    case InProgress:
                        outcomeText = "Still in play";
                        break;
                    case NoughtWin:
                        outcomeText = "Player 2 wins";
                        break;
                    case CrossWin:
                        outcomeText = "Player 1 wins";
                        break;
                    case Draw:
                        outcomeText = "Draw";
                        break;
                }

                winnerText.setText(gRenderer, const_cast<char *>(outcomeText.c_str()), OFF_BLACK);
                completed = true;
            }

            clickToContinueText.render(gRenderer, clickToContinueTopLeft);
            winnerText.render(gRenderer, {gridOffset.x, gridOffset.y + GRID_LENGTH + TEXT_PADDING});
        }

        for (auto &tile: tiles) {
            tile.render(gRenderer);
        }

        drawGrid(gRenderer, gridOffset, GRID_LENGTH, 12, OFF_BLACK);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
