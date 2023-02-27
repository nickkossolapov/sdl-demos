#ifndef NOUGHTS_AND_CROSSES_TILE_H
#define NOUGHTS_AND_CROSSES_TILE_H

#include <SDL.h>
#include <optional>
#include "states.h"

enum State {
    None,
    Hover,
    MouseDown,
    Selected
};

class Tile {
public:
    Tile(SDL_Point center, int length) ;
    void handleEvent(SDL_Event *e, PlayState &currentPlayer);
    void render(SDL_Renderer *renderer);

private:
    SDL_Point mPosition;
    SDL_Point mCenter;
    int mLength;
    State mState;
    std::optional<PlayState> mSelected;
    int drawCrossForGridItem(SDL_Renderer *renderer, Uint8 colour);
    int drawNoughtForGridItem(SDL_Renderer *renderer, Uint8 colour);
};

#endif //NOUGHTS_AND_CROSSES_TILE_H
