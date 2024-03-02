#ifndef PROFESOR_H
#define PROFESOR_H

#include "Idioma.hh"
#include "Usuario.hh"
#include "Curso.hh"
#include "DTUsuario.hh"
#include "DTEstadisticaCurso.hh"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Profesor : public Usuario {
    private:
        string instituto;
        set<Idioma*> idiomas;

        vector<Curso*> cursosCreados;

    public:
        Profesor(string, string, string, string, string, set<Idioma*>);
        ~Profesor(){};

        bool creoElCurso(string);//devuelve true si el profesor creó el curso pasado
        vector<string> getIdiomasConocidos();
        DTUsuario* getDTUsuario() override;
        vector<DTEstadisticaCurso> getEstadisticasP();
        
        void addCursoCreado(Curso*);
        void removeCursoCreado(string);
};


#endif
