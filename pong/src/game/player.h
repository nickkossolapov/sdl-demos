#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "paddle.h"

class Player {
public:
    explicit Player(Paddle &paddle);

    void handleEvent(const SDL_Event &e) const;

private:
    const float JOYSTICK_MAX_LIMIT = (float) Paddle::MAX_VELOCITY / SDL_MAX_SINT16;
    Paddle &mPaddle;
};

#endif //PLAYER_H
