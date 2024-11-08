#ifndef ASTEROID_H
#define ASTEROID_H

#include <array>
#include <cmath>
#include <random>

#include "body2d.h"

class Asteroid final : public Body2d {
public:
    int scale;
    int size = 20;
    bool hasCollided = false;

    explicit Asteroid(int _scale, std::mt19937 &rng);

    Asteroid(Asteroid const &other) = default;

    Asteroid(Asteroid &&other) noexcept = default;

    Asteroid &operator=(Asteroid const &other) = default;

    Asteroid &operator=(Asteroid &&other) noexcept = default;

    void draw() const override;

    void update() override;

    bool isColliding(const Vector &point) const;

private:
    explicit Asteroid(const int _scale)
        : Body2d(static_cast<float>(_scale), static_cast<float>(_scale)),
          scale(_scale), vertices(std::array<Vector, 12>()), originalVertices(vertices) {
    }

    float cornerLength = std::sqrt(2.0f) * static_cast<float>(scale) * static_cast<float>(size);
    std::array<Vector, 12> originalVertices;
    std::array<Vector, 12> vertices;
};

#endif //ASTEROID_H
