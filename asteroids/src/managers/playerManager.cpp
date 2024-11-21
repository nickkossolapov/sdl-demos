#include "playerManager.h"

void PlayerManager::update() {
    if (player.hasCollided) {
        player.hasCollided = false;
        lives.decrement();
        player.reset();
        lastSpawnedAt = SDL_GetTicks();
        player.isInvincible = true;
    }

    if (SDL_GetTicks() - lastSpawnedAt > 5000) {
        player.isInvincible = false;
    }
}