#include <iostream>
#include "gameStateManager.h"
#include "pausedState.h"

GameStateManager::GameStateManager(SDL_Renderer *renderer, TTF_Font *font) {
    mGameStates[GameStates::IN_GAME] = std::make_unique<InGameState>(renderer, font);
    mGameStates[GameStates::PAUSED] = std::make_unique<PausedState>(renderer, font);
    mCurrentState = GameStates::IN_GAME;
}

void GameStateManager::handleEvent(SDL_Event &e) {
    if ((e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ||
        (e.type == SDL_JOYBUTTONUP && e.jbutton.button == 7)) {
        mCurrentState = mCurrentState == GameStates::IN_GAME ? GameStates::PAUSED : GameStates::IN_GAME;
    } else {
        mGameStates[mCurrentState]->handleEvent(e);
    }
}

void GameStateManager::update() {
    mGameStates[mCurrentState]->update();
}

void GameStateManager::render(SDL_Renderer *renderer) {
    mGameStates[mCurrentState]->render(renderer);
}
