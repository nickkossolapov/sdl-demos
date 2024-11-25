#include <iostream>
#include <SDL.h>
#include <vector>

#include "config/colors.h"
#include "globals.h"
#include "config/config.h"
#include "entities/asteroid.h"
#include "managers/simulation.h"
#include "utils/utils.h"
#include "entities/player.h"
#include "managers/asteroidManager.h"
#include "managers/bulletManager.h"
#include "managers/gameStateManager.h"
#include "managers/lives.h"
#include "utils/text.h"
#include "managers/playerManager.h"

void prepareRenderer(SDL_Renderer* renderer) {
    auto [r, g, b, a] = Colours::grey;
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char* args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    auto bulletManager = BulletManager();
    auto score = Score();
    auto lives = Lives(score);

    auto player = Player(1.0, 1.0, bulletManager);
    player.position = {static_cast<float>(ScreenSize::width) / 2, static_cast<float>(ScreenSize::height) / 2};
    player.update();

    auto playerManager = PlayerManager(player, lives);
    auto asteroidManager = AsteroidManager(5, bulletManager, score, player);

    auto simulation = Simulation(player, bulletManager, asteroidManager);

    auto gameStateManager = GameStateManager(score, playerManager, simulation, player, asteroidManager, lives);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }

            gameStateManager.handleEvent(e);
            player.handleEvent(e);
        }

        player.update();

        simulation.updateSimulation();

        player.updateEdges();
        lives.update();
        asteroidManager.update();
        playerManager.update();

        prepareRenderer(gRenderer);

        player.draw();
        bulletManager.drawBullets();
        asteroidManager.drawAsteroids();
        score.draw();
        lives.draw();

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
