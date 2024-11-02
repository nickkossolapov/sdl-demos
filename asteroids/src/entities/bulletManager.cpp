#include "bulletManager.h"

void BulletManager::addBullet(const Bullet &bullet) {
    bullets.push_back(bullet);
}

void BulletManager::updateBullets(float dt) {
    for (auto &bullet: bullets) {
        bullet.update(dt);
    }
}

void BulletManager::drawBullets() const {
    for (const auto &bullet: bullets) {
        bullet.draw();
    }
}