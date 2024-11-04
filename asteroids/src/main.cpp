#include <iostream>
#include <SDL.h>
#include <vector>

#include "config/colors.h"
#include "globals.h"
#include "managers/simulation.h"
#include "utils/utils.h"
#include "entities/spaceship.h"
#include "managers/bulletManager.h"

void prepareRenderer(SDL_Renderer *renderer) {
    auto [r, g, b, a] = Colours::grey;
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    auto bulletManager = BulletManager();

    auto spaceship = Spaceship(1.0, 1.0, bulletManager);

    spaceship.position.x = 100;
    spaceship.position.y = 100;

    std::vector<std::reference_wrapper<Body2d> > gameObjects = {};

    gameObjects.emplace_back(spaceship);

    auto simulation = Simulation(gameObjects, bulletManager);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }

            spaceship.handleEvent(e);
        }

        for (auto &gameObject: gameObjects) {
            gameObject.get().update();
        }

        simulation.updateSimulation();

        prepareRenderer(gRenderer);

        for (auto &gameObject: gameObjects) {
            gameObject.get().draw();
        }

        bulletManager.drawBullets();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
