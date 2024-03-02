#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>

using namespace std;

class IObserver {
    public:
        virtual void notify(string,string) = 0; //nombreIdioma,nombreCurso
};

#endif