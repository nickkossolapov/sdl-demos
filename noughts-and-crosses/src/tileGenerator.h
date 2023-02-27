#ifndef NOUGHTS_AND_CROSSES_TILEGENERATOR_H
#define NOUGHTS_AND_CROSSES_TILEGENERATOR_H

#include <array>
#include "tile.h"

std::array<Tile, 9> generateTiles(int gridLength, int tileLength, SDL_Point gridOffset);

#endif //NOUGHTS_AND_CROSSES_TILEGENERATOR_H
