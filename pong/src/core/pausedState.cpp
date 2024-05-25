
#include "pausedState.h"
#include "../config/colors.h"
#include "../config/constants.h"

PausedState::PausedState(SDL_Renderer *renderer, TTF_Font *font)
        : mPausedText(TextTexture(font)) {
    mPausedText.setText(renderer, "Paused", FONT_SIZE, OFF_WHITE, OFF_BLACK);
}

void PausedState::render(SDL_Renderer *renderer) {
    mPausedText.render(renderer, {SCREEN_WIDTH / 2 - mPausedText.getWidth() / 2,
                                  SCREEN_HEIGHT / 2 - mPausedText.getHeight() / 2});
}
