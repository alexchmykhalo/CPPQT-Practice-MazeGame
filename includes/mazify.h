#ifndef MAZIFY_H
#define MAZIFY_H

#include "game-defs.h"

void mazify(std::array<std::array<char, mazeColumns>, mazeRows> &maze, int x1, int x2, int y1, int y2);

#endif // MAZIFY_H
