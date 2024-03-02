#ifndef DTINFOEJERCICIOC_H
#define DTINFOEJERCICIOC_H

#include <iostream>
#include "DTInfoEjercicio.hh"

#include <vector>
#include <string>

using namespace std;

class DTInfoEjercicioC: public DTInfoEjercicio{
    private:
        vector<string> solucion;
    public:
        DTInfoEjercicioC(string,string,vector<string>);
        ~DTInfoEjercicioC(){};

        void showInfoEjercicio();
};

#endif