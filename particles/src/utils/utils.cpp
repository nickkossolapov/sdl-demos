#include <SDL.h>
#include "../config/config.h"
#include "../globals.h"
#include "utils.h"

void init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        exit(1);
    }

    if (TTF_Init() == -1) {
        exit(2);
    }
    gWindow = SDL_CreateWindow("Particles", 700, 400, ScreenSize::width, ScreenSize::height, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        exit(3);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        exit(4);
    }

    if (SDL_NumJoysticks() >= 1) {
        gGameController = SDL_JoystickOpen(0);
        if (gGameController == nullptr) {
            exit(6);
        }
    }
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    TTF_Quit();
    SDL_Quit();
}
