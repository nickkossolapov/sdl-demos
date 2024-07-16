#include <array>
#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "entities/particle.h"
#include "config/config.h"
#include "entities/simulation.h"

void prepareRenderer(SDL_Renderer *renderer) {
    auto background = Colours::white;
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    int offset = 20;
    auto particleInitialArea = SDL_Rect{offset, offset, ScreenSize::width - (2 * offset), ScreenSize::height / 3};

    int numParticles = 1000;
    auto simulation = Simulation(numParticles, particleInitialArea);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        simulation.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
