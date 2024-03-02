#ifndef DTDATE_H
#define DTDATE_H

#include <iostream>

using namespace std;

class DTDate
{
private:
    int day, month, year;

public:
    DTDate(int, int, int);
    DTDate(string);
    DTDate();
    DTDate getDate();
    ~DTDate();
    int getDay();
    int getMonth();
    int getYear();
    void showDate();
};

#endif