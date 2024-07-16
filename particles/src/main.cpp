#include <array>
#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "entities/particle.h"

void prepareRenderer(SDL_Renderer *renderer) {
    auto background = Colours::white;
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    auto particle = Particle();

    particle.position.x = 100;
    particle.position.y = 100;
    particle.radius = 3;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        particle.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
