#ifndef ASTEROIDS_SHAPES_H
#define ASTEROIDS_SHAPES_H

// Get the y-coordinates that lies on the edge of a circle using the midpoint circle algorithm https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
// Note: this only returns the edges in the first quadrant for the algorithm
void getCircleEdgePoints(int coords[], int coordsLength, int radius);

#endif //ASTEROIDS_SHAPES_H
