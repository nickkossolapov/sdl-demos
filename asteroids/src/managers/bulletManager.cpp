#include "bulletManager.h"

#include "../globals.h"
#include <SDL_render.h>

void BulletManager::addBullet(const Bullet &bullet) {
    if (bullets.size() < 4) {
        bullets.push_back(bullet);
    }
}

void BulletManager::updateBullets(const float dt) {
    for (int i = 0; i < bullets.size();) {
        bullets[i].update(dt);

        if (bullets[i].isOffScreen() || bullets[i].isDestroyed) {
            std::swap(bullets[i], bullets.back());
            bullets.pop_back();
        } else {
            i++;
        }
    }
}

void BulletManager::drawBullets() const {
    for (const auto &bullet: bullets) {
        bullet.draw();
    }
}
