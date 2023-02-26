#include <SDL.h>
#include <algorithm>
#include "colours.h"

// Get the y-coordinate that lies on the edge of a circle using the midpoint circle algorithm https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
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


int drawNought(SDL_Renderer *renderer, int centreX, int centreY, int innerRadius, int outerRadius) {
    if (outerRadius < innerRadius || innerRadius < 0) {
        return -1;
    }

    int result = 0;
    result |= SDL_SetRenderDrawColor(renderer, OFF_BLACK, OFF_BLACK, OFF_BLACK, 0xFF);

    // Multiply by sin(45) because that's where the quadrant will end
    int outerLength = (int)(outerRadius*0.7+1);
    int innerLength = (int)(innerRadius*0.7+1);

    int outerCoordinates[outerLength];
    int innerCoordinates[innerLength];

    getCircleEdgePoints(outerCoordinates, outerLength, outerRadius);
    getCircleEdgePoints(innerCoordinates, innerLength, innerRadius);

    for (int i = 0; i < outerLength; i++) {
        int outerX = outerCoordinates[i];
        int innerX = i >= innerLength ? i : innerCoordinates[i];

        for (int j = innerX; j < outerX; ++j) {
            result |= SDL_RenderDrawPoint(renderer, centreX + j, centreY + i);
            result |= SDL_RenderDrawPoint(renderer, centreX + i, centreY + j);
            result |= SDL_RenderDrawPoint(renderer, centreX - j, centreY - i);
            result |= SDL_RenderDrawPoint(renderer, centreX - i, centreY - j);
            result |= SDL_RenderDrawPoint(renderer, centreX + j, centreY - i);
            result |= SDL_RenderDrawPoint(renderer, centreX + i, centreY - j);
            result |= SDL_RenderDrawPoint(renderer, centreX - j, centreY + i);
            result |= SDL_RenderDrawPoint(renderer, centreX - i, centreY + j);
        }
    }

    return result;
}

int drawCross(SDL_Renderer *renderer, int centreX, int centreY, int width, int thickness){
    if (width < 0 || thickness < 0) {
        return -1;
    }

    int result = 0;

    result |= SDL_SetRenderDrawColor(renderer, OFF_BLACK, OFF_BLACK, OFF_BLACK, 0xFF);
    // Convert the thickness to x-offset for 45 degree line
    int offset = (int)(thickness*0.7);
    int apo = width/2;

    for (int i = 0; i < apo; i++) {
        for (int j = 0; j < apo; j++) {
            if (!(i + j > width - offset || i - j > offset - 1 || i - j < -offset + 1)){
                SDL_RenderDrawPoint(renderer, centreX + i, centreY + j);
                SDL_RenderDrawPoint(renderer, centreX - i, centreY - j);
                SDL_RenderDrawPoint(renderer, centreX + i, centreY - j);
                SDL_RenderDrawPoint(renderer, centreX - i, centreY + j);
            }

        }
    }
}
