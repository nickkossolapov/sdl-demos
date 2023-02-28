#ifndef NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
#define NOUGHTS_AND_CROSSES_SHAPEDRAWER_H

#include <SDL.h>

void drawNought(SDL_Renderer *renderer, SDL_Point &center, int innerRadius, int outerRadius, Uint8 colour);
void drawCross(SDL_Renderer *renderer, SDL_Point &center, int halfLength, int thickness, Uint8 colour);
void drawGrid(SDL_Renderer *renderer, SDL_Point &topLeft, int length, int thickness, Uint8 colour);

#endif //NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
