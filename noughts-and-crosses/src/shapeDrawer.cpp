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


void drawNought(SDL_Renderer *renderer, SDL_Point center, const int innerRadius, const int outerRadius, Uint8 colour) {
    if (outerRadius < innerRadius || innerRadius < 0) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, colour, colour, colour, 0xFF);

    // Multiply by sin(45) because that's where the quadrant will end
    int outerLength = (int) (outerRadius * 0.7 + 1);
    int innerLength = (int) (innerRadius * 0.7 + 1);

    int outerCoordinates[outerLength];
    int innerCoordinates[innerLength];

    getCircleEdgePoints(outerCoordinates, outerLength, outerRadius);
    getCircleEdgePoints(innerCoordinates, innerLength, innerRadius);

    for (int i = 0; i < outerLength; i++) {
        int outerX = outerCoordinates[i];
        int innerX = i >= innerLength ? i : innerCoordinates[i];

        for (int j = innerX; j < outerX; ++j) {
            SDL_RenderDrawPoint(renderer, center.x + j, center.y + i);
            SDL_RenderDrawPoint(renderer, center.x + i, center.y + j);
            SDL_RenderDrawPoint(renderer, center.x - j, center.y - i);
            SDL_RenderDrawPoint(renderer, center.x - i, center.y - j);
            SDL_RenderDrawPoint(renderer, center.x + j, center.y - i);
            SDL_RenderDrawPoint(renderer, center.x + i, center.y - j);
            SDL_RenderDrawPoint(renderer, center.x - j, center.y + i);
            SDL_RenderDrawPoint(renderer, center.x - i, center.y + j);
        }
    }
}

void drawCross(SDL_Renderer *renderer, SDL_Point center, const int halfLength, const int thickness, Uint8 colour) {
    if (halfLength < 0 || thickness < 0) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, colour, colour, colour, 0xFF);

    // Convert the thickness to y-offset for 45 degree line (sin45~=0.7)
    int offset = (int) (thickness * 0.7);

    for (int i = 0; i < halfLength; i++) {
        for (int j = 0; j < halfLength; j++) {
            if (!(i + j > halfLength * 2 - offset || i - j > offset - 1 || i - j < -offset + 1)) {
                SDL_RenderDrawPoint(renderer, center.x + i, center.y + j);
                SDL_RenderDrawPoint(renderer, center.x - i, center.y - j);
                SDL_RenderDrawPoint(renderer, center.x + i, center.y - j);
                SDL_RenderDrawPoint(renderer, center.x - i, center.y + j);
            }

        }
    }
}

void drawGrid(SDL_Renderer *renderer, SDL_Point topLeft, int length, int thickness, Uint8 colour) {
    if (thickness < 0 || length < thickness) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, colour, colour, colour, 0xFF);

    SDL_Rect row1 = {topLeft.x, topLeft.y + length / 3 - thickness / 2, length, thickness};
    SDL_Rect row2 = {topLeft.x, topLeft.y + 2 * length / 3 - thickness / 2, length, thickness};
    SDL_Rect column1 = {topLeft.x + length / 3 - thickness / 2, topLeft.y, thickness, length};
    SDL_Rect column2 = {topLeft.x + 2 * length / 3 - 2 * thickness / 2, topLeft.y, thickness, length};

    SDL_RenderFillRect(renderer, &row1);
    SDL_RenderFillRect(renderer, &row2);
    SDL_RenderFillRect(renderer, &column1);
    SDL_RenderFillRect(renderer, &column2);
}
