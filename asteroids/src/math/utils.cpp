#include "./utils.h"

float radiansToDegrees(float const radians) {
    return radians * (180.0f / 3.14159f);
}

float sign(Vector const &p1, Vector const &p2, Vector const &p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}


// https://stackoverflow.com/a/2049593
bool isInTriangle(Vector const &point, Vector const &v1, Vector const &v2, Vector const &v3) {
    float d1 = sign(point, v1, v2);
    float d2 = sign(point, v2, v3);
    float d3 = sign(point, v3, v1);

    bool hasNeg = d1 < 0 || d2 < 0 || d3 < 0;
    bool hasPos = d1 > 0 || d2 > 0 || d3 > 0;

    return !(hasNeg && hasPos);
}



