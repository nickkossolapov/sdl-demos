#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "tile.h"
#include "shapeDrawer.h"
#include "utils.h"
#include "tileGenerator.h"


void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    auto cross = PlayState::Nought;

    const SDL_Point gridOffset = {20, 20 };
    const int gridLength = 630;

    auto tiles = generateTiles(gridLength, 130, gridOffset);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            for (auto &tile: tiles) {
                tile.handleEvent(&e, cross);
            }
        }

        prepareRenderer(gRenderer);

        for (auto &tile: tiles) {
            tile.render(gRenderer);
        }

        drawGrid(gRenderer, gridOffset, gridLength, 12, OFF_BLACK);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
