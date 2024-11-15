#include "lives.h"

#include <cmath>

#include "../globals.h"
#include "../config/colors.h"

void drawPlayerLife(const int _x, const int _y) {
    auto x = static_cast<float>(_x);
    auto y = static_cast<float>(_y);

    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    float tipLength = 20;
    float wingLength = 12;

    float tipX = x;
    float tipY = y - tipLength;

    constexpr float finAngle = 2.356194f; // 135 degrees
    constexpr float sinFinAngle = -std::sin(finAngle);
    constexpr float cosFinAngle = -std::cos(finAngle);

    float leftEndX = x - sinFinAngle * wingLength / 2;
    float leftEndY = y + cosFinAngle * wingLength / 2;
    float leftWingX = x - sinFinAngle * wingLength;
    float leftWingY = y + cosFinAngle * wingLength;

    float rightEndX = x + sinFinAngle * wingLength / 2;
    float rightEndY = y + cosFinAngle * wingLength / 2;
    float rightWingX = x + sinFinAngle * wingLength;
    float rightWingY = y + cosFinAngle * wingLength;

    SDL_RenderDrawLineF(gRenderer, tipX, tipY, leftWingX, leftWingY);
    SDL_RenderDrawLineF(gRenderer, tipX, tipY, rightWingX, rightWingY);
    SDL_RenderDrawLineF(gRenderer, rightEndX, rightEndY, rightWingX, rightWingY);
    SDL_RenderDrawLineF(gRenderer, leftEndX, leftEndY, leftWingX, leftWingY);
    SDL_RenderDrawLineF(gRenderer, leftEndX, leftEndY, rightEndX, rightEndY);
}

void Lives::draw() const {
    for (int i = 0; i < lives; i++) {
        int x = 200;
        int y = 100;
        int gap = 20;

        drawPlayerLife(x - i * gap, y);
    }
};

void Lives::update() {
    if (score.getScore() - lastBonusLifeAt > 10000 && lives < maxLives) {
        lastBonusLifeAt = score.getScore();
        lives++;
    }
}
