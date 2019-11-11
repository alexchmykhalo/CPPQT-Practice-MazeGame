#ifndef CURSESHELPERUTILS_H
#define CURSESHELPERUTILS_H

#include <pdcurses/curses.h>
#include <string>

void initTerminalWindow(bool isEchoOn, int delay = -1);
int readKeyFromTerminalWindow();
void clearPreviousInput();
void applyChangesToTerminalWindow();
void printCharToTerminalWindow(int x, int y, chtype ch);
void shutdownTerminalWindow();
void printStringToTerminalWindow(int x, int y, chtype ch, const std::string &str);

#endif // CURSESHELPERUTILS_H
