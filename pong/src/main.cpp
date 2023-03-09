#include <SDL.h>
#include "colors.h"
#include "globals.h"
#include "utils.h"
#include "paddle.h"
#include "constants.h"
#include "ball.h"
#include "player.h"
#include "cpuPlayer.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, 0xFF);
    SDL_RenderClear(renderer);
}

int SDL_main() {
    init();

    bool quit = false;
    SDL_Event e;

    std::vector<Paddle> paddles{
            Paddle({
                           PADDING,
                           PADDING,
                           Paddle::PADDLE_WIDTH,
                           SCREEN_HEIGHT - 2 * PADDING
                   }),
            Paddle({
                           SCREEN_WIDTH - PADDING - Paddle::PADDLE_WIDTH,
                           PADDING,
                           Paddle::PADDLE_WIDTH,
                           SCREEN_HEIGHT - 2 * PADDING
                   })
    };

    auto ball = Ball({10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20});
    auto player = Player(paddles[0]);
    auto cpuPlayer = CpuPlayer(paddles[1], ball);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_JOYBUTTONDOWN) {
                ball.reset();
            }

            player.handleEvent(e);
        }

        cpuPlayer.movePaddle();

        for (auto &paddle: paddles) {
            paddle.move();
        }
        ball.move(paddles);

        prepareRenderer(gRenderer);

        for (auto &paddle: paddles) {
            paddle.render(gRenderer);
        }
        ball.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
