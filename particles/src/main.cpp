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
    SDL_Rect particleInitialArea = {
            offset,
            2 * ScreenSize::height / 3 - offset,
            ScreenSize::width - (2 * offset),
            ScreenSize::height / 4
    };

    int obstacleOffset = 30;
    SDL_Rect obstacleInitialArea = {
            obstacleOffset,
            2 * obstacleOffset,
            ScreenSize::width - (2 * obstacleOffset),
            ScreenSize::height / 4
    };

    constexpr int numParticles = 1000;
    constexpr int numObstacles = 15;
    auto simulation = Simulation(numParticles, particleInitialArea, numObstacles, obstacleInitialArea);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        simulation.updateSimulation();

        simulation.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
