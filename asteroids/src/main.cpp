#include <iostream>
#include <SDL.h>
#include <vector>

#include "config/colors.h"
#include "globals.h"
#include "config/config.h"
#include "entities/asteroid.h"
#include "managers/simulation.h"
#include "utils/utils.h"
#include "entities/spaceship.h"
#include "managers/asteroidManager.h"
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
    auto asteroidManager = AsteroidManager(bulletManager);

    auto spaceship = Spaceship(1.0, 1.0, bulletManager);
    spaceship.position = {static_cast<float>(ScreenSize::width) / 2, static_cast<float>(ScreenSize::height) / 2};

    auto simulation = Simulation(spaceship, bulletManager, asteroidManager);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }

            spaceship.handleEvent(e);
        }

        spaceship.update();
        asteroidManager.update();

        simulation.updateSimulation();

        prepareRenderer(gRenderer);

        spaceship.draw();
        bulletManager.drawBullets();
        asteroidManager.drawAsteroids();


        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
