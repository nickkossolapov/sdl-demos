#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include <SDL.h>
#include "body2d.h"

class Spaceship : public Body2d {
public:
    explicit Spaceship(float mass, float inertia);

    void handleEvent(const SDL_Event &e);

    void draw() const override;
};

#endif //ASTEROIDS_SPACESHIP_H
