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

        vertices[i] = vertex * dist(rng) * static_cast<float>(scale) * static_cast<float>(size);
    }

    originalVertices = vertices;
}

void Asteroid::update() {
    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    for (int i = 0; i < 12; ++i) {
        vertices[i] = {
            originalVertices[i].x * dCos - originalVertices[i].y * dSin,
            originalVertices[i].x * dSin + originalVertices[i].y * dCos,
        };
    }
}


void Asteroid::draw() const {
    if (hasCollided) {
        return;
    }

    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, 0x00, 0x00, 0xFF);

    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    std::vector<SDL_FPoint> squareVertices = {
        {position.x + dCos * cornerLength, position.y + dSin * cornerLength},
        {position.x + dSin * cornerLength, position.y - dCos * cornerLength},
        {position.x - dCos * cornerLength, position.y - dSin * cornerLength},
        {position.x - dSin * cornerLength, position.y + dCos * cornerLength},
    };

    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        SDL_RenderDrawLineF(gRenderer, squareVertices[i].x, squareVertices[i].y, squareVertices[j].x,
                            squareVertices[j].y);
    }

    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    for (int i = 0; i < 12; ++i) {
        int j = (i + 1) % 12;
        SDL_RenderDrawLineF(
            gRenderer,
            vertices[i].x + position.x,
            vertices[i].y + position.y,
            vertices[j].x + position.x,
            vertices[j].y + position.y);
    }
}

bool Asteroid::isColliding(Vector const &point) const {
    if ((point - position).length() > cornerLength) {
        return false;
    }

    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    float paddedLength = cornerLength + 2.0f;

    // Vertices
    Vector v1 = {position.x + dCos * paddedLength, position.y + dSin * paddedLength};
    Vector v2 = {position.x + dSin * paddedLength, position.y - dCos * paddedLength};
    Vector v3 = {position.x - dCos * paddedLength, position.y - dSin * paddedLength};
    Vector v4 = {position.x - dSin * paddedLength, position.y + dCos * paddedLength};

    return isInTriangle(point, v1, v2, v3) || isInTriangle(point, v2, v3, v4);
}
