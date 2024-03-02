#ifndef DTESTADISTICACURSO_H
#define DTESTADISTICACURSO_H

#include "DTDificultad.hh"

#include <iostream>
#include <string>

using namespace std;

class DTEstadisticaCurso {
    private:
        string name, description, idioma;
        Dificultad difficulty;
        float progress;
    public:
        DTEstadisticaCurso(string,string,string,Dificultad,float);
        ~DTEstadisticaCurso(){};

        string getName();
        string getDescription();
        string getIdioma();
        Dificultad getDifficulty();
        float getProgress();
};

#endif