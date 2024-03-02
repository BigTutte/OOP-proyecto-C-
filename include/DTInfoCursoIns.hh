#ifndef DTINFOCURSOINS_H
#define DTINFOCURSOINS_H

#include "DTDificultad.hh"

#include <iostream>
#include <vector>

using namespace std;


class DTInfoCursoIns{
    private:
        string name, description;
        Dificultad difficulty;
        int cantLecciones;
        vector<int> cantEjercicios;
    public:
        DTInfoCursoIns(string,string,Dificultad,int,vector<int>);
        ~DTInfoCursoIns();
        string getName();
        string getDescription();
        Dificultad getDifficulty();
        int getCantLecciones();
        vector<int> getCantEjercicios();
        int getCantEjerciciosTotal();

};

#endif