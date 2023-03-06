#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    Paddle(SDL_Rect playBoundary);

    void handleEvent(SDL_Event &e);

    void move();

    void render(SDL_Renderer *renderer);

    SDL_Rect &getCollisionBox();

private:
    static const int PADDLE_HEIGHT = 20;
    static const int PADDLE_WIDTH = 20;

    const float MAX_VELOCITY = 10;
    const float JOYSTICK_MAX_LIMIT = MAX_VELOCITY / SDL_MAX_SINT16;

    SDL_Rect mBoundingRect{};
    SDL_Rect mPaddleRect{};
    float mVelX, mVelY;
};

#endif //PADDLE_H
