#include "asteroid.h"

#include <cmath>
#include <SDL.h>
#include <vector>

#include "../config/colors.h"
#include "../globals.h"

void Asteroid::draw() const {
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    float static length = std::sqrt(2.0f) * static_cast<float>(scale) * static_cast<float>(size);

    float dCos = std::cos(orientation);
    float dSin = std::sin(orientation);

    std::vector<SDL_FPoint> vertices = {
        {position.x + dCos * length, position.y + dSin * length},
        {position.x + dSin * length, position.y - dCos * length},
        {position.x - dCos * length, position.y - dSin * length},
        {position.x - dSin * length, position.y + dCos * length},
    };

    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        SDL_RenderDrawLineF(gRenderer, vertices[i].x, vertices[i].y, vertices[j].x, vertices[j].y);
    }
}
