#ifndef ASTEROIDS_BULLETMANAGER_H
#define ASTEROIDS_BULLETMANAGER_H

#include <vector>
#include "../entities/bullet.h"

class BulletManager {
public:
    void addBullet(const Bullet &bullet);

    void updateBullets(float dt);

    void drawBullets() const;

    std::vector<Bullet> &getBullets() {
        return bullets;
    };

private:
    std::vector<Bullet> bullets;
};

#endif //ASTEROIDS_BULLETMANAGER_H
