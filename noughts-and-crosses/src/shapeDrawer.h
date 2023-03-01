#ifndef NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
#define NOUGHTS_AND_CROSSES_SHAPEDRAWER_H

#include <SDL.h>

void drawNought(SDL_Renderer *renderer, SDL_Point &center, int innerRadius, int outerRadius, SDL_Color color);
void drawCross(SDL_Renderer *renderer, SDL_Point &center, int halfLength, int thickness, SDL_Color color);
void drawGrid(SDL_Renderer *renderer, SDL_Point &topLeft, int length, int thickness, SDL_Color color);

#endif //NOUGHTS_AND_CROSSES_SHAPEDRAWER_H
