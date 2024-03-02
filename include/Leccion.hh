#ifndef LECCION_H
#define LECCION_H

#include "DTInfoLeccion.hh"

#include <vector>
#include <string>
#include <iostream>

class Ejercicio;
class Curso;

using namespace std;

class Leccion {
    private:
        string topic, objective;

        vector<Ejercicio*> compuestaPor;
        Ejercicio* ejerSave;

    public:
        Leccion(string,string);
        ~Leccion();
        
        bool hayEjer();
        DTInfoLeccion* getInfoLeccion();
        string getTopic();
        int cantEjercicios();
        int getCantEjerciciosAprobL(string);
        vector<string> getEjerciciosPendientes(string);
        string getLetraEjercicio(string);
        bool compararSolucion(string);
        bool estaCompletaLeccion(string);
        
        void addEjercicioC(string,string,vector<string>);
        void addEjercicioT(string,string,string);
        void deleteExercices();

        //test
        //vector<Ejercicio*> getEjercicios(){return compuestaPor;};
};

#include "Ejercicio.hh"
#include "Curso.hh"
#endif