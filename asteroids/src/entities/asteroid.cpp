#include "asteroid.h"

#include <cmath>
#include <SDL.h>
#include <vector>

#include "../config/colors.h"
#include "../globals.h"
#include "../math/utils.h"

Asteroid::Asteroid(const int _scale, std::mt19937 &rng)
        : Body2d(static_cast<float>(_scale), static_cast<float>(_scale)),
          scale(_scale), vertices(std::array<Vector, 12>()) {
    std::uniform_real_distribution<float> dist(0.5, 1.0);

    for (int i = 0; i < 12; ++i) {
        Vector vertex = {
                std::cos(static_cast<float>(i) * 3.14159f / 6),
                std::sin(static_cast<float>(i) * 3.14159f / 6),
        };

        vertices[i] = vertex * dist(rng) * radius;
    }

    originalVertices = vertices;
}

void Asteroid::update() {
    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    for (int i = 0; i < 12; ++i) {
        vertices[i] = {
                originalVertices[i].x * dCos - originalVertices[i].y * dSin + position.x,
                originalVertices[i].x * dSin + originalVertices[i].y * dCos + position.y,
        };
    }
}


void Asteroid::draw() const {
    if (hasCollided) {
        return;
    }

    auto [r, g, b, a] = Colours::white;

    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    for (int i = 0; i < 12; ++i) {
        int j = (i + 1) % 12;
        SDL_RenderDrawLineF(
                gRenderer,
                vertices[i].x,
                vertices[i].y,
                vertices[j].x,
                vertices[j].y);
    }
}

bool Asteroid::isColliding(Vector const &point) const {
    if ((point - position).length() > radius) {
        return false;
    }

    for (int i = 0; i < 12; ++i) {
        int j = (i + 1) % 12;

        if (isInTriangle(point, vertices[i], vertices[j], position)) {
            return true;
        }
    }

    return false;
}
