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

    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xFF);

    for (int i = 0; i < bullets.size(); i++) {
        for (int j = -1; j < 2; ++j) {
            SDL_RenderDrawPoint(gRenderer, 10 + i, 10 + j);
        }
    }
}
