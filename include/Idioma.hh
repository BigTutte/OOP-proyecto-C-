#ifndef IDIOMA_H
#define IDIOMA_H

#include "IObserver.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Idioma {
    private:
        string name;
        vector<IObserver*> observers;
    public:
        Idioma(string);
        ~Idioma();

        string getName();
        bool isObserver(IObserver*);
        
        void addObserver(IObserver*);
        void removeObserver(IObserver*);
        void notifyObservers(string);
};

#endif