#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "Usuario.hh"
#include "Inscripcion.hh"
#include "DTDate.hh"
#include "DTUsuario.hh"
#include "DTEstadisticaCursoEstudiante.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Estudiante : public Usuario {
    private:
        string country;
        DTDate date;

        vector<Inscripcion*> inscripciones;
        Inscripcion* insSave;

    public:
        Estudiante(string, string, string, string, string, DTDate);
        ~Estudiante(){};

        void addInscripcion(Inscripcion*);

        DTUsuario* getDTUsuario() override;
        vector<DTEstadisticaCursoEstudiante> getEstadisticasE();
        vector<string> getCursosNoAprobados();
        vector<string> getEjerciciosPendientes(string);
        string getLetraEjercicio(string);
        Inscripcion* getInsSave();

        void eraseInscription(Inscripcion*);
        bool compararSolucion(string);
};

#endif
