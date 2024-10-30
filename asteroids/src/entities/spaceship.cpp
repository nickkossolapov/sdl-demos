#include <cmath>

#include "./spaceship.h"
#include "../globals.h"
#include "../config/colors.h"

Spaceship::Spaceship(float mass, float inertia) : Body2d(mass, inertia) {}

void Spaceship::handleEvent(const SDL_Event &e) {
    // todo
}

void Spaceship::draw() const {
    auto [x, y, _] = position;
    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    // todo: figure out angles

    float tipX = x + std::cos(orientation) * 80;
    float tipY = y + std::sin(orientation) * 80;

    float rearLeftX = x - std::cos(orientation - 135) * 50;
    float rearLeftY = y + std::sin(orientation - 135) * 50;

    float rearRightX = x - std::cos(orientation + 135) * 50;
    float rearRightY = y + std::sin(orientation + 135) * 50;

    SDL_RenderDrawLineF(gRenderer, tipX, tipY, rearLeftX, rearLeftY);
    SDL_RenderDrawLineF(gRenderer, tipX, tipY, rearRightX, rearRightY);
    SDL_RenderDrawLineF(gRenderer, rearLeftX, rearLeftY, rearRightX, rearRightY);
}

