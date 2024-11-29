#include "gameStateManager.h"

#include "../config/config.h"
#include "../utils/text.h"


void GameStateManager::handleEvent(const SDL_Event &e) {
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

void GameStateManager::draw() {
    if (gameState == GameState::WelcomeScreen) {
        static auto welcomeString = "Press any key to start";
        auto [width, height] = Text::getStringWidthAndHeight(welcomeString);
        Text::drawString(welcomeString, ScreenSize::width / 2 - width / 2, ScreenSize::height / 2 - height / 2);
    }
}

void GameStateManager::update() {
    if (isInGame()) {
        if (playerManager.isGameOver()) {
            gameState = GameState::GameOver;
        }
    }
}
