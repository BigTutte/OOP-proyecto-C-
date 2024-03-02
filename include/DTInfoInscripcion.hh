#ifndef DTINFOINSCRIPCION_H
#define DTINFOINSCRIPCION_H

#include "DTDate.hh"

#include <string>

using namespace std;

class DTInfoInscripcion{
    private:
        string nombreEstudiante;
        DTDate fechaInsc;
    public:
        DTInfoInscripcion(string,DTDate);
        ~DTInfoInscripcion(){};

        void showInfoInscripcion();
};

#endif