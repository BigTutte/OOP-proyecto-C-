#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "DTDate.hh"
#include "DTInfoInscripcion.hh"
#include "DTEstadisticaCursoEstudiante.hh"

#include <iostream>
#include <vector>

class Curso;
class Estudiante;

using namespace std;

class Inscripcion {
    private:
        DTDate inscriptionDate;
        bool approved;

        Curso* curso;
        Estudiante* estudiante;

    public:
        Inscripcion(DTDate);
        Inscripcion(Curso*,DTDate);
        ~Inscripcion(){};

        DTInfoInscripcion* getInfoInscripcion();
        string getNickEstudiante();
        DTEstadisticaCursoEstudiante getStudentStatistic(string);
        float getPorcentajeAvanceE(string);
        bool getApproved();
        string getNombreCurso();
        vector<string> getEjerciciosPendientes(string);
        string getLetraEjercicio(string);
        bool compararSolucion(string);
        bool estaCompletaLeccion(string);
        bool estaAprobadoCurso();

        void setApproved(bool);

        void unroll();
};

#include "Curso.hh"
#include "Estudiante.hh"
#endif