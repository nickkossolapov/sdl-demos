#include "./spaceship.h"
#include "../globals.h"
#include "../config/colors.h"

Spaceship::Spaceship(float mass, float inertia) : Body2d(mass, inertia) {}

void Spaceship::handleEvent(const SDL_Event &e) {
    // todo
}

void Spaceship::draw() const {
    auto [x, y, _] = position;
    auto background = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, background.r, background.g, background.b, 0xFF);

    SDL_RenderDrawLineF(gRenderer, x, y, x + 50, y + 50);
}

