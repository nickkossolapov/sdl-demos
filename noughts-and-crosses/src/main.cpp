#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "gridItem.h"
#include "shapeDrawer.h"
#include "utils.h"


void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    auto currentPlayer = std::rand() % 2 == 0 ? PlayState::Cross : PlayState::Nought;
    GridItem gridItem = GridItem(200, 200, 150);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            gridItem.handleEvent(&e, currentPlayer);
        }

        prepareRenderer(gRenderer);

        gridItem.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
