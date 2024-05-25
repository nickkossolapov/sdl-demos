#ifndef PONG_PAUSEDSTATE_H
#define PONG_PAUSEDSTATE_H

#include <SDL.h>
#include "../utils/textTexture.h"
#include "gameState.h"

class PausedState : public GameState {
public:
    explicit PausedState(SDL_Renderer *renderer, TTF_Font *font);

    void render(SDL_Renderer *renderer) override;

private:
    TextTexture mPausedText;
};

#endif //PONG_PAUSEDSTATE_H
