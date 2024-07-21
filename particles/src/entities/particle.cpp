#include "particle.h"
#include "../constants.h"
#include "../globals.h"
#include "../utils/shapes.h"
#include "../config/config.h"

Particle::Particle(float radius, SDL_Color colour) : radius(radius), colour(colour),
                                                     area(Constants::Pi * radius * radius) {
    mass = 1.0;
    speed = 0.0;
}

void Particle::calcLoads() {
    netForce = {0.0f, 0.0f};

    if (isColliding) {
        netForce += impactForce;
    } else {
        netForce.y = -Constants::Gravity * mass;

        Vector drag = velocity.reversed();
        drag.normalize();

        drag *= 0.5f * Constants::AirDensity * dragCoefficient * area * speed * speed;
    }
}

void Particle::updateBodyEuler(float dt) {
    previousPosition = position;
    Vector a = netForce / mass;
    Vector dv = a * dt;
    velocity += dv;

    Vector ds = velocity * dt;
    position += ds * Constants::ScaleFactor;

    speed = velocity.length();
}

void Particle::draw() const {
    SDL_SetRenderDrawColor(gRenderer, colour.r, colour.g, colour.b, 0xFF);

    auto center = SDL_Point{static_cast<int>(position.x), ScreenSize::height - static_cast<int>(position.y)};

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
