#ifndef PARTICLES_SHAPES_H
#define PARTICLES_SHAPES_H


// Get the y-coordinates that lies on the edge of a circle using the midpoint circle algorithm https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
// Note: this only returns the edges in the first quadrant for the algorithm
void getCircleEdgePoints(int coords[], int coordsLength, int radius);

#endif //PARTICLES_SHAPES_H
