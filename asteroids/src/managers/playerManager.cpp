#include "playerManager.h"

void PlayerManager::update() {
    if (player.hasCollided) {
        player.hasCollided = false;
        lives.decrement();
        player.reset();
    }
}