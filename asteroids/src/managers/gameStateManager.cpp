#include "gameStateManager.h"

#include "../config/config.h"
#include "../utils/text.h"


void GameStateManager::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYUP) {
        if (gameState == GameState::GameOver && SDL_GetTicks() - gameOverAt > 2000) {
            playerManager.reset();
            player.reset();
            score.reset();
            asteroidManager.reset();
            lives.reset();

            gameState = GameState::Playing;
            simulation.pause(false);
        } else if (gameState == GameState::WelcomeScreen) {
            simulation.pause(false);
            gameState = GameState::Playing;
        }
    }
}

void GameStateManager::draw() {
    auto midScreenWidth = static_cast<float>(ScreenSize::width) / 2;
    auto midScreenHeight = static_cast<float>(ScreenSize::height) / 2;

    if (gameState == GameState::WelcomeScreen) {
        static auto startString = "Press any key to start";
        auto [width, height] = Text::getStringWidthAndHeight(startString);
        Text::drawString(startString, midScreenWidth - width / 2, midScreenHeight - height / 2);
    } else if (gameState == GameState::GameOver) {
        float gap = 150;

        static auto gameOverString = "Game over";
        auto [gameOverHeight, gameOverWidth] = Text::getStringWidthAndHeight(gameOverString);
        Text::drawString(gameOverString, midScreenWidth - gameOverHeight / 2, midScreenHeight - gameOverWidth / 2 - gap);

        static auto scoreString = "Your score is " + std::to_string(score.getScore());
        auto [scoreHeight, scoreWidth] = Text::getStringWidthAndHeight(scoreString);
        Text::drawString(scoreString, midScreenWidth - scoreHeight / 2, midScreenHeight - scoreWidth / 2);

        static auto tryAgainString = "Press any key to try again";
        auto [tryAgainWidth, tryAgainHeight] = Text::getStringWidthAndHeight(tryAgainString);
        Text::drawString(tryAgainString, midScreenWidth - tryAgainWidth / 2, midScreenHeight - tryAgainHeight / 2 + gap);
    }
}

void GameStateManager::update() {
    if (isInGame()) {
        if (playerManager.isGameOver()) {
            gameState = GameState::GameOver;
            gameOverAt = SDL_GetTicks();
            simulation.pause(true);
        }
    }
}
