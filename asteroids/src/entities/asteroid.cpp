#include "asteroid.h"

#include <cmath>
#include <SDL.h>
#include <vector>

#include "../config/colors.h"
#include "../globals.h"
#include "../math/utils.h"

void Asteroid::draw() const {
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    if (hasCollided) {
        SDL_SetRenderDrawColor(gRenderer, r, 0x00, 0x00, 0xFF);
    }


    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    std::vector<SDL_FPoint> vertices = {
        {position.x + dCos * cornerLength, position.y + dSin * cornerLength},
        {position.x + dSin * cornerLength, position.y - dCos * cornerLength},
        {position.x - dCos * cornerLength, position.y - dSin * cornerLength},
        {position.x - dSin * cornerLength, position.y + dCos * cornerLength},
    };

    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        SDL_RenderDrawLineF(gRenderer, vertices[i].x, vertices[i].y, vertices[j].x, vertices[j].y);
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
