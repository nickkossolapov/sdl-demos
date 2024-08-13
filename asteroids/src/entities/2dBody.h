#ifndef ASTEROIDS_2DBODY_H
#define ASTEROIDS_2DBODY_H

#include "../math/vector.h"

class Body2d {
public:
    float mass;
    float inertia;
    Vector position;
    Vector velocity;

    Body2d(float inertia);

    void calcLoads();

    void updateBodyEuler(float dt);

    void draw() const;
};

#endif //ASTEROIDS_2DBODY_H
