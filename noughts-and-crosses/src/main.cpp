#include <SDL.h>
#include "colours.h"
#include "globals.h"
#include "gridItem.h"
#include "shapeDrawer.h"
#include "utils.h"


void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    auto cross = PlayState::Cross;
    auto nought = PlayState::Nought;

    GridItem gridItem1 = GridItem({105, 105}, 150);
    GridItem gridItem2 = GridItem({105, 315}, 150);
    GridItem gridItem3 = GridItem({105, 525}, 150);
    GridItem gridItem4 = GridItem({315, 105}, 150);
    GridItem gridItem5 = GridItem({315, 315}, 150);
    GridItem gridItem6 = GridItem({315, 525}, 150);
    GridItem gridItem7 = GridItem({525, 105}, 150);
    GridItem gridItem8 = GridItem({525, 315}, 150);
    GridItem gridItem9 = GridItem({525, 525}, 150);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            gridItem1.handleEvent(&e, cross);
            gridItem2.handleEvent(&e, nought);
            gridItem3.handleEvent(&e, cross);
            gridItem4.handleEvent(&e, nought);
            gridItem5.handleEvent(&e, cross);
            gridItem6.handleEvent(&e, nought);
            gridItem7.handleEvent(&e, cross);
            gridItem8.handleEvent(&e, nought);
            gridItem9.handleEvent(&e, cross);
        }

        prepareRenderer(gRenderer);

        gridItem1.render(gRenderer);
        gridItem2.render(gRenderer);
        gridItem3.render(gRenderer);
        gridItem4.render(gRenderer);
        gridItem5.render(gRenderer);
        gridItem6.render(gRenderer);
        gridItem7.render(gRenderer);
        gridItem8.render(gRenderer);
        gridItem9.render(gRenderer);

        drawGrid(gRenderer, {0, 0}, 630, 12, OFF_BLACK);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
