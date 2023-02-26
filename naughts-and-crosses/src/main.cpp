#include <SDL.h>
#include "utils.h"
#include "globals.h"
#include "constants.h"
#include <tuple>


void prepareRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, OFF_WHITE, OFF_WHITE, OFF_WHITE, 0xFF);
    SDL_RenderClear(renderer);
}

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


int drawNaught(SDL_Renderer *renderer, int centreX, int centreY, int innerRadius, int outerRadius) {
    if (outerRadius < innerRadius || innerRadius < 0) {
        return -1;
    }

    int result = 0;
    result |= SDL_SetRenderDrawColor(renderer, OFF_BLACK, OFF_BLACK, OFF_BLACK, 0xFF);

    // Multiply by sqrt(2)/2 because that's where the quadrant will end (sin(45))
    auto outerLength = (int)(outerRadius*0.7+1);
    auto innerLength = (int)(innerRadius*0.7+1);

    int outerCoordinates[outerLength];
    int innerCoordinates[innerLength];

    getCircleEdgePoints(outerCoordinates, outerLength, outerRadius);
    getCircleEdgePoints(innerCoordinates, innerLength, innerRadius);

    for (int i = 0; i < outerLength; i++) {
        auto outerX = outerCoordinates[i];
        auto innerX = i >= innerLength ? i : innerCoordinates[i];

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

int main(int argc, char *args[]) {
    init();

    bool quit = false;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        prepareRenderer(gRenderer);

        drawNaught(gRenderer, 150, 150, 60, 75);

        SDL_RenderPresent( gRenderer );
    }

    close();

    return 0;
}
