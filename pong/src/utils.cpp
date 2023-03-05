#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#include "globals.h"
#include "utils.h"

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        exit(1);
    }

    if (TTF_Init() == -1) {
        exit(2);
    }
    gWindow = SDL_CreateWindow("Pong", 700, 400, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        exit(3);
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        exit(4);
    }

    gFont = TTF_OpenFont("fonts/arcadeclassic.ttf", FONT_SIZE);
    if (gFont == nullptr) {
        exit(5);
    };
}

void close() {
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    TTF_Quit();
    SDL_Quit();
}

