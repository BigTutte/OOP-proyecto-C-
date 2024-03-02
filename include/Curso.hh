#ifndef CURSO_H
#define CURSO_H

#include "DTDificultad.hh"
#include "Inscripcion.hh"
#include "DTInfoCurso.hh"
#include "Idioma.hh"
#include "DTEstadisticaCurso.hh"

#include <iostream>
#include <vector>
#include <string>

class Leccion;
class EstadisticaCurso;

using namespace std;

class Curso {
    private:
        string name, description;
        Dificultad difficulty;
        bool available;
        Idioma* elCursoEsDe;

        unsigned int idLeccion;

        vector<Leccion*> compuestoPor;

        vector<Curso*> previas;
        vector<Inscripcion*> inscripciones;

    public:
        Curso(string,string,Dificultad,Idioma*);
        ~Curso();

        string getName();
        string getDescription();
        Dificultad getDifficulty();
        int getCantLecciones();
        vector<int> getCantEjercicios();
        int getCantEjerciciosAprobC(string);
        bool isAvailable();
        DTInfoCurso* getInfoCurso();
        vector<string> listLessons();
        bool estaInscripto(string);
        bool cumpleLasPrevias(string);
        DTEstadisticaCurso getEstadisticaC();
        bool aproboElCurso(string);
        vector<string> getEjerciciosPendientes(string);
        string getLetraEjercicio(string);
        bool compararSolucion(string);
        bool estaCompletaLeccion(string);
        bool estaAprobadoCurso();

        void setIdLeccion(int);
        void setElCursoEsDe(Idioma*);
        void addPrevia(Curso*);
        void addLeccion(string,string);
        void addEjercicioCEnLid(string,string,vector<string>);
        void addEjercicioTEnLid(string,string,string);
        void addInscripcion(DTDate);
        bool habilitar();
        void deleteCourse();
        void sacarPrevia(string);

        //test
        //vector<Leccion*> getLecciones(){return compuestoPor;};
};

#include "Leccion.hh"
#endif