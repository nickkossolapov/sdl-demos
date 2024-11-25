#include "gameStateManager.h"

void GameStateManager::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYUP) {
        // if (gameState == GameState::GameOver) {
        if (e.key.keysym.sym == SDLK_q) {
            playerManager.reset();
            player.reset();
            score.reset();
            asteroidManager.reset();
            lives.reset();

            gameState = GameState::WelcomeScreen;
            simulation.pause(true);
        } else if (gameState == GameState::WelcomeScreen) {
            simulation.pause(false);
            gameState = GameState::Playing;
        }
    }
}

void GameStateManager::update() {
    if (inGame) {
        if (playerManager.isGameOver()) {
            gameState = GameState::GameOver;
        }
    }
}
