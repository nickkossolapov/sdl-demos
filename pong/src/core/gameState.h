#ifndef PONG_GAMESTATE_H
#define PONG_GAMESTATE_H

#include <SDL.h>

class GameState {
public:
    virtual ~GameState() {}

    virtual void handleEvent(SDL_Event &e) {};

    virtual void update() {};

    virtual void render(SDL_Renderer *renderer) = 0;
};

#endif //PONG_GAMESTATE_H
