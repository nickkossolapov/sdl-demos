#include <array>
#include <SDL.h>
#include "config/colors.h"
#include "globals.h"
#include "utils/utils.h"
#include "game/paddle.h"
#include "game/ball.h"
#include "game/player.h"
#include "game/cpuPlayer.h"
#include "ui/scoreUi.h"
#include "core/gameStateManager.h"

void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;
    SDL_Event e;

    auto gameStateManager = GameStateManager(gRenderer, gFont);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            gameStateManager.handleEvent(e);
        }

        gameStateManager.update();
        prepareRenderer(gRenderer);
        gameStateManager.render(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
