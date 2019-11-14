
// Файл main.cpp

#include <iostream>
#include <string>

#include "game-defs.h"
#include "game-map-utils.h"

#include "curses-helper-utils.h"

#include "random-utils.h"

// Checks if user want so play
// Return true if user wants to play; false otherwise

//------------------------------
void generateWallsInside(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    const int down{1};
    const int right{2};

    int mazeSize{0};

    if(mazeRows % 2 == 0)
    {
        mazeSize = 2;
    }
    else
    {
        mazeSize = 1;
    }

    for(size_t row{1}; row < (mazeRows - 1); ++row)
    {
        for(size_t column{1}; column < (mazeColumns - 1); ++column)
        {
            if((row % 2 != 0) && (column % 2 != 0))
            {
                prMaze[row][column] = emptySymbol;

                if((column == (mazeColumns - (mazeSize + 1))) && (row == (mazeRows - (mazeSize + 1))))
                {
                    prMaze[row][column] = emptySymbol;
                }
                else if((column == (mazeColumns - (mazeSize + 1))) && ((row + 2) < (mazeRows - mazeSize)))
                {
                    prMaze[row + 1][column] = emptySymbol;
                    prMaze[row + 2][column] = emptySymbol;
                }
                else if((row == (mazeRows - (mazeSize + 1))) && ((column + 2) < (mazeColumns - mazeSize)))
                {
                    prMaze[row][column + 1] = emptySymbol;
                    prMaze[row][column + 2] = emptySymbol;
                }
                else
                {
                    int whereToGo = generateRandomNumber(down, right);

                    if(whereToGo == down)
                    {
                        if((row + 2) < (mazeRows - mazeSize))
                        {
                            prMaze[row + 1][column] = emptySymbol;
                            prMaze[row + 2][column] = emptySymbol;
                        }
                    }
                    else if(whereToGo == right)
                    {
                        if((column + 2) < (mazeColumns - mazeSize))
                        {
                            prMaze[row][column + 1] = emptySymbol;
                            prMaze[row][column + 2] = emptySymbol;
                        }
                    }
                }
            }
        }
    }
}

void placeExit(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    int randomRow = generateRandomNumber(1, (mazeRows - 2));
    while(randomRow % 2 == 0)
    {
        randomRow = generateRandomNumber(1, (mazeRows - 2));
    }

    int randomColumn = generateRandomNumber(1, (mazeRows - 2));
    while(randomColumn % 2 == 0)
    {
        randomColumn = generateRandomNumber(1, (mazeRows - 2));
    }

    int counterOfWalls{0};

    if(((randomColumn + 1) < mazeColumns) && (prMaze[randomRow][randomColumn + 1] == wallSymbol))
    {
        ++counterOfWalls;
    }

    if(((randomColumn - 1) > 0) && (prMaze[randomRow][randomColumn - 1] == wallSymbol))
    {
        ++counterOfWalls;
    }

    if (((randomRow + 1) < mazeRows) && (prMaze[randomRow + 1][randomColumn] == wallSymbol))
    {
        ++counterOfWalls;
    }

    if (((randomRow - 1) > 0) && (prMaze[randomRow - 1][randomColumn] == wallSymbol))
    {
        ++counterOfWalls;
    }

    if(counterOfWalls == 3)
    {
        prMaze[randomRow][randomColumn] = exitSymbol;
        return;
    }
    else
    {
        placeExit(prMaze);
    }
}
//-------------------------------

bool doesUserWantsToPlay()
{
    bool rResult = false;

    std::cout << "Maze Game" << std::endl;

    while (true)
    {
        std::cout << "Do you want to play? (1 - yes, 0 - no):";

        std::string answer;
        std::cin >> answer;

        if ((answer == "1") || (answer == "0"))
        {
            rResult = (answer == "1");
            break;
        }

        std::cout << "Sorry, I did not understand." << std::endl;
    }

    return rResult;
}

// Generates maze
// Parameters:
//       maze - reference to maze field that will be modified
//              (walls added, added character and exit)
void generateMaze(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    for (int row = 0; row < mazeRows; row++)
    {
        for (int column = 0; column < mazeColumns; column++)
        {
            prMaze[row][column] = wallSymbol;
        }
    }

    //Walls generation
    generateWallsInside(prMaze);
    placeExit(prMaze);

    // Place character
    placeCharRandomly(prMaze, characterSymbol, 1);
}

// Moves character according to given command and retuns eaten symbol (if any)
// Parameters:
//      row - character row position
//      column - character column position
//      command - test string with given command ("l" - left, "r" - right, "u" - up, "d" - down)
//      prMaze - reference to maze field; will be modified as a result of command execution
char moveAndGather(int row,
                   int column,
                   char command,
                   std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    char rCharMovedOnto = emptySymbol;

    // Take character out from map
    prMaze[row][column] = emptySymbol;

    if (command == 'l')
    {
        rCharMovedOnto = prMaze[row][column - 1];

        if (rCharMovedOnto != wallSymbol)
        {
            column--;
        }
    }

    if (command == 'r')
    {
        rCharMovedOnto = prMaze[row][column + 1];

        if (rCharMovedOnto != wallSymbol)
        {
            column++;
        }
    }

    if (command == 'u')
    {
        rCharMovedOnto = prMaze[row - 1][column];

        if (rCharMovedOnto != wallSymbol)
        {
            row--;
        }
    }

    if (command == 'd')
    {
        rCharMovedOnto = prMaze[row + 1][column];

        if (rCharMovedOnto != wallSymbol)
        {
            row++;
        }
    }

    // Place character back with new position
    prMaze[row][column] = characterSymbol;

    return rCharMovedOnto;
}

// Prints message to player.
// Parameters:
//      message - text message to player
void gameMessage(const std::string& message)
{
    std::cout << std::endl << message << std::endl << std::endl;
}

// Moves character and check if exit was found as a result of that move.
// Parameters:
//      prMaze - reference to maze field; will be modified while player moves.
bool moveCharacterAndCheckIfExitFound(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    bool rExitFound = false;

    int charRow = 1;
    int charColumn = 1;
    if (scanForChar(prMaze, characterSymbol, charRow, charColumn))
    {
//        std::cout << "Command (l - left, r - right, u - up, d- down):";
        char command = readKeyFromTerminalWindow();
//        std::cin >> command;

        const char charMovedOnto = moveAndGather(charRow, charColumn, command, prMaze);

        if (charMovedOnto == wallSymbol)
        {
            gameMessage("Cannot move here!");
        }

        if (charMovedOnto == exitSymbol)
        {
            gameMessage("Exit found!");
            rExitFound = true;
        }
    }
    else
    {
        gameMessage("Error: cannot find char!");
    }

    return rExitFound;
}

// Executes one round of the game
void playMazeGame()
{
    std::cout << "LETS START!" << std::endl;

    std::array<std::array<char, mazeColumns>, mazeRows> maze;
    generateMaze(maze);

    do
    {
        drawMaze(maze);
        applyChangesToTerminalWindow();
    }
    while (!moveCharacterAndCheckIfExitFound(maze));
}

int main()
{
//    while (doesUserWantsToPlay())
    initTerminalWindow(false, 0);
    clearPreviousInput();
    {
        playMazeGame();
    }
    shutdownTerminalWindow();
}
