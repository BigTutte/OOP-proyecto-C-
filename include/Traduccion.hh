#ifndef TRADUCCION_H
#define TRADUCCION_H

#include "Ejercicio.hh"
#include "DTInfoEjercicio.hh"

#include <iostream>
#include <string>

using namespace std;

class Traduccion : public Ejercicio {
    private:
        string phraseToTranslate, translation;
    public:
        Traduccion(string,string,string);
        ~Traduccion();

        DTInfoEjercicio* getInfoEjercicio();
        string getLetra();
        bool compararSolucion(string);

        //test
        //string getSolucion(){return this->translation;};
};

#endif