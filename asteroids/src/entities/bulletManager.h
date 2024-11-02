#ifndef ASTEROIDS_BULLETMANAGER_H
#define ASTEROIDS_BULLETMANAGER_H

#include <vector>
#include "bullet.h"

class BulletManager {
public:
    void addBullet(const Bullet &bullet);

    void updateBullets(float dt);

    void drawBullets() const;

private:
    std::vector<Bullet> bullets;
};

#endif //ASTEROIDS_BULLETMANAGER_H
