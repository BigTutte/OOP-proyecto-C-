#ifndef COMPLETAR_H
#define COMPLETAR_H

#include "Ejercicio.hh"

#include <iostream>
#include <vector>

using namespace std;

class CompletarPalabra : public Ejercicio {
    private:
        string phraseToComplete;
        vector<string> solution;
    public:
        CompletarPalabra(string,string,vector<string>);
        ~CompletarPalabra();

        DTInfoEjercicio* getInfoEjercicio();
        string getLetra();
        bool compararSolucion(string);

        //test
        //string getSolucion(){string s; for(unsigned int i=0;i<this->solution.size();++i){s+=this->solution[i];if(i!=this->solution.size()-1){s+=",";}}return s;};
};

#endif