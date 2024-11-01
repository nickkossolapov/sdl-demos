#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "entities/spaceship.h"

void prepareRenderer(SDL_Renderer *renderer) {
    auto [r, g, b, a] = Colours::grey;
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
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
            if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }

            spaceship.handleEvent(e);
        }

        prepareRenderer(gRenderer);

        spaceship.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
