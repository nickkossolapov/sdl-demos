#include <SDL.h>
#include "utils.h"
#include "globals.h"
#include "colours.h"
#include "shapeDrawer.h"


void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        drawNought(gRenderer, 150, 150, 60, 75);
        drawCross(gRenderer, 300, 300, 150, 18);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
