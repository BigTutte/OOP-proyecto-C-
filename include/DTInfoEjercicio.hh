#ifndef DTINFOEJERCICIO_H
#define DTINFOEJERCICIO_H

#include <iostream>
#include <string>

using namespace std;

class DTInfoEjercicio{
    private:
        string descripcion, consigna;
    public:
        DTInfoEjercicio(string,string);
        virtual ~DTInfoEjercicio() = 0;

        string getDescripcion();
        string getConsigna();
        virtual void showInfoEjercicio() = 0;
};

#endif