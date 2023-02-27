#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "shapeDrawer.h"
#include "utils.h"
#include "tileGenerator.h"
#include "gameState.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;
    auto tiles = generateTiles(GRID_LENGTH, TILE_SIZE, GRID_OFFSET);
    GameState gameState = {tiles };

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
                    auto winningLine = gameState.tryGetWinningLine();
                    gameState.reset();
                    tiles = tiles = generateTiles(GRID_LENGTH, TILE_SIZE, GRID_OFFSET);
                }
            }
        }

        prepareRenderer(gRenderer);

        for (auto &tile: tiles) {
            tile.render(gRenderer);
        }

        drawGrid(gRenderer, GRID_OFFSET, GRID_LENGTH, 12, OFF_BLACK);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
