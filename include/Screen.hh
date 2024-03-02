#ifndef SCREEN_H
#define SCREEN_H

#ifdef _WINDOWS
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <iostream>

using namespace std;

void setXY(ostream& os, int x, int y);
void clearScreen();

#endif