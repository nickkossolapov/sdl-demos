#include "bulletManager.h"

void BulletManager::addBullet(const Bullet &bullet) {
    bullets.push_back(bullet);
}

void BulletManager::updateBullets(float dt) {
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
