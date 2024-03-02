#ifndef DTINFOLECCION_H
#define DTINFOLECCION_H

#include "DTInfoEjercicio.hh"

#include <vector>
#include <string>

using namespace std;

class DTInfoLeccion{
    private:
        string tema, objetivo;
        vector<DTInfoEjercicio*> ejercicios;
    public:
        DTInfoLeccion(string,string,vector<DTInfoEjercicio*>);
        ~DTInfoLeccion();

        void showInfoLeccion();
};

#endif