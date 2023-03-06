#include <SDL.h>
#include "colors.h"
#include "globals.h"
#include "utils.h"
#include "paddle.h"
#include "constants.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;

    auto player1 = Paddle({10, 10, 30, SCREEN_HEIGHT-20});

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            player1.handleEvent(e);
        }

        player1.move();

        prepareRenderer(gRenderer);

        player1.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
