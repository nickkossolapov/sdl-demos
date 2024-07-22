#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SDL.h>

#include "../config/colors.h"
#include "../math/Vector.h"

class Obstacle
{
public:
    Vector position;
    float radius;

    explicit Obstacle(const Vector& position, float radius = 30, SDL_Color colour = Colours::grey);

    void draw() const;

private:
    SDL_Color colour;
};

#endif //OBSTACLE_H
