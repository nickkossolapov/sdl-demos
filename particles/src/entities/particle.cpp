#include "particle.h"
#include "../constants.h"
#include "../globals.h"
#include "../utils/shapes.h"
#include "../config/colors.h"

Particle::Particle(float radius, SDL_Color colour) : radius(radius), colour(colour) {
    mass = 1.0;
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
    velocity.x = 0.0;
    velocity.y = 0.0;
    velocity.z = 0.0;
    speed = 0.0;
    netForce.x = 0.0;
    netForce.y = 0.0;
    netForce.z = 0.0;
}

void Particle::calcLoads() {
    netForce.y = Constants::Gravity * mass;
}

void Particle::updateBodyEuler(float dt) {
    Vector a = netForce / mass;
    Vector dv = a * dt;
    velocity += dv;

    Vector ds = velocity * dt;
    position += ds;

    speed = velocity.length();
}

void Particle::draw() const {
    SDL_SetRenderDrawColor(gRenderer, colour.r, colour.g, colour.b, 0xFF);

    auto center = SDL_Point{static_cast<int>(position.x), static_cast<int>(position.y)};

    // Multiply by sin(45) because that's where the quadrant will end
    int edgeCount = (int) (radius * 0.7 + 1);
    int edgePoints[edgeCount];

    getCircleEdgePoints(edgePoints, edgeCount, static_cast<int>(radius));


    for (int i = 0; i < edgeCount; i++) {
        int edge = edgePoints[i];

        for (int j = 0; j < edge; ++j) {
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
