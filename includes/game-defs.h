#ifndef GAME_MAP_DEFS_H
#define GAME_MAP_DEFS_H

#include <array>

const int mazeColumns = 65;
const int mazeRows = 25;

const char emptySymbol = ' ';
const char wallSymbol = 'X';
const char characterSymbol = '@';
const char exitSymbol = '#';
const char keySymbol = '&';
const char scoreSymbol1 = '1';
const char scoreSymbol2 = '2';
const char scoreSymbol3 = '3';

//using Map = std::array<std::array<char, cMazeColumns>, cMazeRows>;

#endif //GAME_MAP_DEFS_H
