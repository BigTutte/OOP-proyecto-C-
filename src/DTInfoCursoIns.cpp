#include "../include/DTInfoCursoIns.hh"
#include "../include/DTDificultad.hh"

#include <vector>

using namespace std;

DTInfoCursoIns::DTInfoCursoIns(string name, string des, Dificultad dif, int cL, vector<int> cE)
{
    this->name=name;
    this->description=des;
    this->difficulty=dif;
    this->cantLecciones=cL;
    this->cantEjercicios=cE;
}

DTInfoCursoIns::~DTInfoCursoIns()
{
}

string DTInfoCursoIns::getName()
{
    return this->name;
}

string DTInfoCursoIns::getDescription()
{
    return this->description;
}

Dificultad DTInfoCursoIns::getDifficulty()
{
    return this->difficulty;
}

int DTInfoCursoIns::getCantLecciones()
{
    return this->cantLecciones;
}

vector<int> DTInfoCursoIns::getCantEjercicios()
{
    return this->cantEjercicios;
}

int DTInfoCursoIns::getCantEjerciciosTotal()
{
    int total=0;
    for (unsigned int i=0; i<this->cantEjercicios.size(); i++)
    {
        total+=this->cantEjercicios[i];
    }
    return total;
}
