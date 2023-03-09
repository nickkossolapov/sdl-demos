#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    static const int PADDLE_HEIGHT = 100;
    static const int PADDLE_WIDTH = 20;
    static const int MAX_VELOCITY = 20;

    Paddle(SDL_Rect playBoundary);

    void move();

    void setVelocity(float velocity);

    void render(SDL_Renderer *renderer);

    SDL_Rect &getCollisionBox();

private:
    SDL_Rect mBoundingRect{};
    SDL_Rect mPaddleRect{};
    float mVelY;
};

#endif //PADDLE_H
