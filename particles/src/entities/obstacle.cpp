#include "obstacle.h"
#include "../globals.h"
#include "../utils/shapes.h"
#include "../config/config.h"


Obstacle::Obstacle(const Vector& position, const float radius, const SDL_Color colour) : position(position),
    radius(radius), colour(colour)
{
}

void Obstacle::draw() const
{
    SDL_SetRenderDrawColor(gRenderer, colour.r, colour.g, colour.b, 0xFF);

    const auto center = SDL_Point{static_cast<int>(position.x), ScreenSize::height - static_cast<int>(position.y)};

    // Multiply by sin(45) because that's where the quadrant will end
    const int edgeCount = static_cast<int>(radius * 0.7 + 1);
    int edgePoints[edgeCount];

    getCircleEdgePoints(edgePoints, edgeCount, static_cast<int>(radius));


    for (int i = 0; i < edgeCount; i++)
    {
        int edge = edgePoints[i];

        for (int j = 0; j < edge; ++j)
        {
            SDL_RenderDrawPoint(gRenderer, center.x + j, center.y + i);
            SDL_RenderDrawPoint(gRenderer, center.x + i, center.y + j);
            SDL_RenderDrawPoint(gRenderer, center.x - j, center.y - i);
            SDL_RenderDrawPoint(gRenderer, center.x - i, center.y - j);
            SDL_RenderDrawPoint(gRenderer, center.x + j, center.y - i);
            SDL_RenderDrawPoint(gRenderer, center.x + i, center.y - j);
            SDL_RenderDrawPoint(gRenderer, center.x - j, center.y + i);
            SDL_RenderDrawPoint(gRenderer, center.x - i, center.y + j);
        }
    }
}

