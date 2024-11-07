#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>

#include "body2d.h"

class Asteroid final : public Body2d {
public:
    int scale;
    int size = 15;
    bool hasCollided = false;

    explicit Asteroid(const int _scale)
        : Body2d(static_cast<float>(_scale), static_cast<float>(_scale)),
          scale(_scale) {
    }

    Asteroid(Asteroid const &other) = default;

    Asteroid(Asteroid &&other) noexcept = default;

    Asteroid &operator=(Asteroid const &other) = default;

    Asteroid &operator=(Asteroid &&other) noexcept = default;

    void draw() const override;

    void update() override {
    }

    bool isColliding(const Vector &point) const;

private:
    float cornerLength = std::sqrt(2.0f) * static_cast<float>(scale) * static_cast<float>(size);
};

#endif //ASTEROID_H
