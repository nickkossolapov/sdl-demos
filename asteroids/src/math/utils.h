#ifndef ASTEROIDS_UTILS_H
#define ASTEROIDS_UTILS_H
#include "vector.h"

float radiansToDegrees(float radians);

bool isInTriangle(Vector const &point, Vector const &v1, Vector const &v2, Vector const &v3);

#endif //ASTEROIDS_UTILS_H
