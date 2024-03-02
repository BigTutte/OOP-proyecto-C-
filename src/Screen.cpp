#include "../include/Screen.hh"
#include <iostream>

void setXY(ostream& os, int x, int y) {
    os << "\033[" << y << ";" << x << "H";
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; //system(CLEAR);
}