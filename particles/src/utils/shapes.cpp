#include <SDL.h>
#include <algorithm>

// Get the y-coordinates that lies on the edge of a circle using the midpoint circle algorithm https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
// Note: this only returns the edges in the first quadrant for the algorithm
void getCircleEdgePoints(int coords[], int coordsLength, int radius) {
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    for (int i = 0; i < coordsLength || x >= y; ++i) {
        coords[i] = x;

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            ty += 2;
            error += (tx - diameter);
        }
    }

    // Only get the outermost y for each x coordinate
    // Since we'll be filling the circle in, we don't care about when there are two pixels in line in the x-axis
    int scanningX;
    for (int i = 0; i < coordsLength; i++) {
        scanningX = std::min(coordsLength - 1, coords[i]);

        coords[i] = std::max(coords[i], coords[scanningX]);
    }
}
