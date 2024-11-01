#ifndef ASTEROIDS_BODY2D_H
#define ASTEROIDS_BODY2D_H

#include "../math/vector.h"

class Body2d {
public:
    virtual ~Body2d() = default;

    float mass;
    float inertia;
    Vector position;
    Vector velocity;
    Vector netForce;
    float orientation; // Radians, 2D, so this represents the z-axis
    float angularVelocity;
    float netMoment;

    Body2d(float mass, float inertia);

    void updateBodyEuler(float dt);

    virtual void draw() const = 0;
};

#endif //ASTEROIDS_BODY2D_H
