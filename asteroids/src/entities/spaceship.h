#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include <SDL.h>
#include "body2d.h"

class Spaceship : public Body2d {
public:
    void handleEvent(const SDL_Event &e);
};

#endif //ASTEROIDS_SPACESHIP_H
