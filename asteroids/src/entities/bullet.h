#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "../math/vector.h"
#include "body2d.h"

class Bullet {
public:
    Bullet(const Vector &_position, const Vector &direction) {
        position = _position;
        velocity = direction * defaultSpeed;
    }

    void draw() const;

    void update(float dt);

private:
    Vector position;
    Vector velocity;

    const float defaultSpeed = 550.0f;
};

#endif //ASTEROIDS_BULLET_H
 