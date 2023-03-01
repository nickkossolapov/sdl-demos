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
    Tile(SDL_Point center, int length);

    void handleEvent(SDL_Event &e, PlayState &currentPlayer);

    void render(SDL_Renderer *renderer);

    State &state();

    void disable();

    void reset();

private:
    SDL_Point mPosition{};
    SDL_Point mCenter{};
    int mLength;
    State mState;
    bool mDisabled;
    std::optional<PlayState> mSelected;

    void drawCrossForGridItem(SDL_Renderer *renderer, SDL_Color color);
    void drawNoughtForGridItem(SDL_Renderer *renderer, SDL_Color color);
};

#endif //NOUGHTS_AND_CROSSES_TILE_H
