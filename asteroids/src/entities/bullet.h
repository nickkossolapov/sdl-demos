#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

#include "../math/vector.h"
#include "body2d.h"

class Bullet {
public:
    Vector position;
    bool isDestroyed = false;

    Bullet(const Vector &_position, const Vector &direction) {
        position = _position;
        velocity = direction * defaultSpeed;
    }

    Bullet &operator=(Bullet &&other) noexcept {
        if (this != &other) {
            position = other.position;
            velocity = other.velocity;
        }

        return *this;
    }

    Bullet(const Bullet &other) = default;

    void draw() const;

    void update(float dt);

    bool isOffScreen() const;

private:
    Vector velocity;

    const float defaultSpeed = 600.0f;
};

#endif //ASTEROIDS_BULLET_H
 
