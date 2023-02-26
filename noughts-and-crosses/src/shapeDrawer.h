#ifndef NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
#define NOUGHTS_AND_CROSSES_SHAPEDRAWER_H

#include <SDL.h>

int drawNought(SDL_Renderer *renderer, int centreX, int centreY, int innerRadius, int outerRadius);
int drawCross(SDL_Renderer *renderer, int centreX, int centreY, int width, int thickness);

#endif //NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
