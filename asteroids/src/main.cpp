#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "entities/spaceship.h"

void prepareRenderer(SDL_Renderer *renderer) {
    auto background = Colours::black;
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    auto spaceship = Spaceship(1.0, 1.0);

    spaceship.position.x = 100;
    spaceship.position.y = 100;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        spaceship.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
