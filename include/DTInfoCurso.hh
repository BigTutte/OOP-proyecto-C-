#ifndef DTINFOCURSO_H
#define DTINFOCURSO_H

#include "DTInfoLeccion.hh"
#include "DTInfoInscripcion.hh"
#include "DTDificultad.hh"

#include <vector>
#include <string>

using namespace std;

class DTInfoCurso{
    private:
        string nombreCurso, descripcionCurso, nombreIdioma, nombreProfesor;
        Dificultad dificultad;
        bool habilitado;
        vector<DTInfoLeccion*> lecciones;
        vector<DTInfoInscripcion*> inscripciones;
    public:
        DTInfoCurso(string, string, Dificultad, bool, string, string, vector<DTInfoLeccion*>, vector<DTInfoInscripcion*>);
        ~DTInfoCurso();

        void showInfoCurso();
};

#endif