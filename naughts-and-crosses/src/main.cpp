#include <SDL.h>
#include "utils.h"
#include "globals.h"

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_UpdateWindowSurface(gWindow);
    }

    close();

    return 0;
}
