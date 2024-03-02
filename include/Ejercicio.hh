#ifndef EJERCICIO_H
#define EJERCICIO_H

#include "DTInfoEjercicio.hh"

#include <vector>
#include <string>
#include <iostream>

class Inscripcion;

using namespace std;

class Ejercicio {
    private:
        string description;

        vector<Inscripcion*> ejercicioAprobado;

    public:
        Ejercicio(string);
        virtual ~Ejercicio(){};

        string getDescription();
        virtual DTInfoEjercicio* getInfoEjercicio()=0;
        bool estaAprobado(string);
        bool estaPendiente(string);
        virtual string getLetra() = 0;
        virtual bool compararSolucion(string) = 0;
        bool estaRealizado(string);

        void setRealizado();

        //test
        //virtual string getSolucion() = 0;
};

#include "Inscripcion.hh"
#endif