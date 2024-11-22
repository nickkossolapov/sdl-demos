#ifndef ASTEROIDS_BODY2D_H
#define ASTEROIDS_BODY2D_H

#include "../math/vector.h"

class Body2d
{
public:
    float mass;
    float inertia;
    Vector position = {0, 0, 0};
    Vector velocity = {0, 0, 0};
    float speed = 0;
    float maxSpeed = 800;
    Vector netForce = {0, 0, 0};
    float orientation = 0; // Radians, 2D, so this represents the z-axis
    float angularVelocity = 0;
    float netMoment = 0;

    Body2d(float mass, float inertia);

    virtual ~Body2d() = default;

    void updateBodyEuler(float dt);

    virtual void update() = 0;

    virtual void draw() const = 0;
};

#endif //ASTEROIDS_BODY2D_H
