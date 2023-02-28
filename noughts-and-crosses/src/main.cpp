#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "shapeDrawer.h"
#include "utils.h"
#include "tileGenerator.h"
#include "gameState.h"
#include "gameover.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;
    SDL_Point gridOffset = {45, 45};
    auto tiles = generateTiles(GRID_LENGTH, TILE_SIZE, gridOffset);
    GameState gameState = {tiles};
    bool completed = false;
    GameOver gameOver = {tiles};

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
                    for (auto &tile: tiles){
                        tile.reset();
                    }
                    gameOver.reset();
                    completed = false;
                }

            }
        }

        if (!completed && gameState.outcome() != Outcome::InProgress) {
            completed = true;

            auto winningLine = gameState.tryGetWinningLine();
            gameOver.setOutcome(gameState.outcome(), winningLine);
        }

        prepareRenderer(gRenderer);

        for (auto &tile: tiles) {
            tile.render(gRenderer);
        }

        drawGrid(gRenderer, gridOffset, GRID_LENGTH, 12, OFF_BLACK);

        gameOver.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
