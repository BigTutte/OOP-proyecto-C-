#ifndef DTESTUDIANTE_H
#define DTESTUDIANTE_H

#include "DTUsuario.hh"
#include "DTDate.hh"

using namespace std;

class DTEstudiante : public DTUsuario {
    private:
        DTDate fechaNacimiento;
        string paisResidencia;

    public:
        DTEstudiante(string,string,DTDate,string);
        ~DTEstudiante(){};
        DTDate getFechaNacimiento();
        string getPaisResidencia();
};

#endif