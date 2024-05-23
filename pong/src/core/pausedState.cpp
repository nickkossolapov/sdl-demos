
#include "pausedState.h"
#include "../config/colors.h"
#include "../config/constants.h"

PausedState::PausedState(SDL_Renderer *renderer, TTF_Font *font)
        : mPausedText(TextTexture(font)),
          mResumeText(TextTexture(font)) {
    mPausedText = TextTexture(font);
    mPausedText.setText(renderer, "Paused", OFF_WHITE, OFF_BLACK);
    mResumeText = TextTexture(font);
    mResumeText.setText(renderer, "Press start or esc to resume", OFF_WHITE, OFF_BLACK);
}

void PausedState::render(SDL_Renderer *renderer) {
    mPausedText.render(renderer, {SCREEN_WIDTH / 2 - mPausedText.getWidth() / 2,
                                  SCREEN_HEIGHT / 2 - mPausedText.getHeight() / 2});
}

