#ifndef DTINFOEJERCICIOT_H
#define DTINFOEJERCICIOT_H

#include <iostream>
#include "DTInfoEjercicio.hh"

#include <string>

using namespace std;

class DTInfoEjercicioT: public DTInfoEjercicio{
    private:
        string solucion;
    public:
        DTInfoEjercicioT(string,string,string);
        ~DTInfoEjercicioT(){};

        void showInfoEjercicio();
};

#endif