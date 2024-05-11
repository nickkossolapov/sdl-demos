#include <array>
#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "game/paddle.h"
#include "config/constants.h"
#include "game/ball.h"
#include "game/player.h"
#include "game/cpuPlayer.h"
#include "game/gameState.h"
#include "ui/scoreUi.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    std::array<Paddle, 2> paddles{
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
    auto gameState = GameState({paddles, ball});
    auto scoreUi = ScoreUi(gFont, gRenderer);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            player.handleEvent(e);

            gameState.handleEvent(e);
        }

        cpuPlayer.movePaddle();
        ball.move(paddles);

        for (auto &paddle: paddles) {
            paddle.move();
        }

        gameState.checkCurrentState();
        scoreUi.setScore(gameState.getScore());

        prepareRenderer(gRenderer);

        for (auto &paddle: paddles) {
            paddle.render(gRenderer);
        }

        ball.render(gRenderer);
        scoreUi.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
