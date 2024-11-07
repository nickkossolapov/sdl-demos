#ifndef ASTEROID_H
#define ASTEROID_H

#include "body2d.h"

class Asteroid final : public Body2d {
public:
    int scale;
    int size = 10;

    explicit Asteroid(const int _scale)
        : Body2d(static_cast<float>(_scale), static_cast<float>(_scale)),
          scale(_scale) {
    }

    void draw() const override;

    void update() override {
    }
};

#endif //ASTEROID_H
