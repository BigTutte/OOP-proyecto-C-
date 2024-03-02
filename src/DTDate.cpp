#include "../include/DTDate.hh"

using namespace std;

DTDate::DTDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

DTDate::DTDate()
{
    this->day = 0;
    this->month = 0;
    this->year = 0;
}

DTDate::DTDate(string date) {
    string delimiter = "/";
    string day = date.substr(0, date.find(delimiter));
    date.erase(0, date.find(delimiter) + delimiter.length());
    string month = date.substr(0, date.find(delimiter));
    date.erase(0, date.find(delimiter) + delimiter.length());
    string year = date.substr(0, date.find(delimiter));
    date.erase(0, date.find(delimiter) + delimiter.length());

    this->day = stoi(day);
    this->month = stoi(month);
    this->year = stoi(year);
}

DTDate DTDate::getDate() {
    return *this;
}

DTDate::~DTDate() {}

int DTDate::getDay() {
    return this->day;
}

int DTDate::getMonth() {
    return this->month;
}

int DTDate::getYear() {
    return this->year;
}

void DTDate::showDate()
{cout<<this->day<<"/"<<this->month<<"/"<<this->year<<endl;}