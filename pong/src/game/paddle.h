#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    static constexpr int PADDLE_HEIGHT = 120;
    static constexpr int PADDLE_WIDTH = 20;
    static constexpr float MAX_VELOCITY = 20;

    explicit Paddle(SDL_Rect playBoundary);

    void move();

    void setVelocity(float velocity);

    void render(SDL_Renderer *renderer) const;

    void reset();

    SDL_Rect &getCollisionBox();

private:
    SDL_Rect mBoundingRect{};
    SDL_Rect mPaddleRect{};
    float mVelY;
};

#endif //PADDLE_H
