#ifndef DTESTADISTICACURSOESTUDIANTE_H
#define DTESTADISTICACURSOESTUDIANTE_H

#include <iostream>
#include <string>

using namespace std;

class DTEstadisticaCursoEstudiante {
    private:
        string course;
        float progress;
    public:
        DTEstadisticaCursoEstudiante(string,float);
        ~DTEstadisticaCursoEstudiante(){};

        string getCourse();
        float getProgress();
};

#endif