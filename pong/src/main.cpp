#include <SDL.h>
#include "colors.h"
#include "globals.h"
#include "utils.h"
#include "paddle.h"
#include "constants.h"
#include "ball.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;

    std::vector<Paddle> players{
            Paddle({10, 10, 30, SCREEN_HEIGHT - 20})
    };

    auto ball = Ball({10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20});

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_JOYBUTTONDOWN) {
                ball.reset();
            }

            for (auto &player: players) {
                player.handleEvent(e);
            }
        }

        for (auto &player: players) {
            player.move();
        }
        ball.move(players);

        prepareRenderer(gRenderer);

        for (auto &player: players) {
            player.render(gRenderer);
        }
        ball.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
