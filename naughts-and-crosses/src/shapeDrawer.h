#ifndef NAUGHTS_AND_CROSSES_SHAPEDRAWER_H
#define NAUGHTS_AND_CROSSES_SHAPEDRAWER_H

#include <SDL.h>

int drawNaught(SDL_Renderer *renderer, int centreX, int centreY, int innerRadius, int outerRadius);
int drawCross(SDL_Renderer *renderer, int centreX, int centreY, int width, int thickness);

#endif //NAUGHTS_AND_CROSSES_SHAPEDRAWER_H
