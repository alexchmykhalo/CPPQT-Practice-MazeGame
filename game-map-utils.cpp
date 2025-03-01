// Файл game-map-utils.cpp

#include "game-map-utils.h"

#include <iostream>
#include "random-utils.h"

#include "curses-helper-utils.h"

// Draws maze onto screen
// Parameters:
//      maze - maze field to draw
void drawMaze(const std::array<std::array<char, mazeColumns>, mazeRows> &maze)
{
    for (int row = 0; row < mazeRows; row++)
    {
        for (int column = 0; column < mazeColumns; column++)
        {
            char ch = maze[row][column];
            if (ch == wallSymbol) {
                printCharToTerminalWindow(column, row, ACS_BLOCK | COLOR_PAIR(8) );
            }

            if (ch == emptySymbol) {
                printCharToTerminalWindow(column, row, emptySymbol | COLOR_PAIR(1) );
            }

            if (ch == characterSymbol) {
                printCharToTerminalWindow(column, row, characterSymbol | COLOR_PAIR(3) );
            }

            if (ch == exitSymbol) {
                printCharToTerminalWindow(column, row, ACS_PI | COLOR_PAIR(6) );
            }

            if (ch == keySymbol) {
                printCharToTerminalWindow(column, row, keySymbol | COLOR_PAIR(4) );
            }

            if (ch == scoreSymbol1) {
                printCharToTerminalWindow(column, row, ACS_DIAMOND | COLOR_PAIR(5) );
            }

            if (ch == scoreSymbol2) {
                printCharToTerminalWindow(column, row, ACS_DIAMOND | COLOR_PAIR(7) );
            }

            if (ch == scoreSymbol3) {
                printCharToTerminalWindow(column, row, ACS_DIAMOND | COLOR_PAIR(8) );
            }


//            std::cout << ch;
        }
//        std::cout << std::endl;
    }
}

// Searches given char on the given maze field,
// returns if found and filling row and column with coordinates
// Parameters:
//      maze - maze field where character will be serched
//      charToFind - char that should be found on maze field
//      rCharRow - reference to row variable for which will be assigned row position
//      rCharColumn - reference to column variable for which will be assigned column position
// Returns true if found; false otherwise.
bool scanForChar(const std::array<std::array<char, mazeColumns>, mazeRows> &maze,
                 const char charToFind,
                 int &rCharRow,
                 int &rCharColumn)
{
    for (int row = 0; row < mazeRows; row++)
    {
        for (int column = 0; column < mazeColumns; column++)
        {
            if (maze[row][column] == charToFind)
            {
                rCharRow = row;
                rCharColumn = column;
                return true;
            }
        }
    }

    return false;
}

// Places given char on the game field in random way,
// omiting replacing existing characters
// Parameters:
//      maze - maze field where character will be serched
//      charToPlace - char that should be placed on maze field
//      charCount - number of chars to place
void placeCharRandomly(std::array<std::array<char, mazeColumns>, mazeRows> &rMaze,
                       char charToPlace,
                       int charCount)
{
    for(int i = 0; i < charCount; i++)
    {
        int randomRow = 0;
        int randomColumn = 0;

        do
        {
            randomRow = generateRandomNumber(0, mazeRows - 1);
            randomColumn = generateRandomNumber(0, mazeColumns - 1);
        }
        while (rMaze[randomRow][randomColumn] != emptySymbol);

        rMaze[randomRow][randomColumn] = charToPlace;
    }
}


