#include "bullet.h"
#include "../globals.h"
#include "../config/colors.h"
#include "../config/config.h"

void Bullet::draw() const {
    if (isDestroyed) {
        return;
    }

    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    auto [r, g, b, a] = Colours::white;
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            SDL_RenderDrawPoint(gRenderer, x + i, y + j);
        }
    }
}

void Bullet::update(float dt) {
    Vector ds = velocity * dt;
    position += ds;
}

bool Bullet::isOffScreen() const {
    return position.x < 0 || position.x > ScreenSize::width || position.y < 0 || position.y > ScreenSize::height;
}

