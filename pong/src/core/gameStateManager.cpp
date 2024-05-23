#include "gameStateManager.h"

GameStateManager::GameStateManager(SDL_Renderer *renderer, TTF_Font *font)
        : mGameStates({InGameState(renderer, font)}) {
    mCurrentState = &mGameStates.inGameState;
}

void GameStateManager::handleEvent(SDL_Event &e) {
    mCurrentState->handleEvent(e);
}

void GameStateManager::update() {
    mCurrentState->update();
}

void GameStateManager::render(SDL_Renderer *renderer) {
    mCurrentState->render(renderer);
}
