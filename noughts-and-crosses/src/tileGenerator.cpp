#include "tileGenerator.h"
#include "tile.h"

std::array<Tile, 9> generateTiles(int gridLength, int tileLength, SDL_Point gridOffset) {
    return {
            Tile({gridLength / 6 + gridOffset.x, gridLength / 6 + gridOffset.y}, tileLength),
            Tile({gridLength / 6 + gridOffset.x, gridLength / 2 + gridOffset.y}, tileLength),
            Tile({gridLength / 6 + gridOffset.x, (5 * gridLength) / 6 + gridOffset.y}, tileLength),
            Tile({gridLength / 2 + gridOffset.x, gridLength / 6 + gridOffset.y}, tileLength),
            Tile({gridLength / 2 + gridOffset.x, gridLength / 2 + gridOffset.y}, tileLength),
            Tile({gridLength / 2 + gridOffset.x, (5 * gridLength) / 6 + gridOffset.y}, tileLength),
            Tile({(5 * gridLength) / 6 + gridOffset.x, gridLength / 6 + gridOffset.y}, tileLength),
            Tile({(5 * gridLength) / 6 + gridOffset.x, gridLength / 2 + gridOffset.y}, tileLength),
            Tile({(5 * gridLength) / 6 + gridOffset.x, (5 * gridLength) / 6 + gridOffset.y}, tileLength)
    };
};
