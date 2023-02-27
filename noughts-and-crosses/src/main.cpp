#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "tile.h"
#include "shapeDrawer.h"
#include "utils.h"
#include "tileGenerator.h"
#include "gameState.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    auto tiles = generateTiles(GRID_LENGTH, 130, GRID_OFFSET);
    GameState gameState = {tiles };

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            for (auto &tile: tiles) {
                tile.handleEvent(e, gameState.currentPlayer());
            }

            gameState.handleEvent(e);
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
