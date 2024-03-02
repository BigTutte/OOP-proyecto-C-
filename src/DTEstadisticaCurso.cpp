#include "../include/DTEstadisticaCurso.hh"
#include "../include/DTDificultad.hh"

#include <string>

using namespace std;

DTEstadisticaCurso::DTEstadisticaCurso(string nomb,string desc,string idi,Dificultad diff,float progreso)
{
    this->name=nomb;
    this->description=desc;
    this->idioma=idi;
    this->difficulty=diff;
    this->progress=progreso;
}



string DTEstadisticaCurso::getName()
{return this->name;}

string DTEstadisticaCurso::getDescription()
{return this->description;}

string DTEstadisticaCurso::getIdioma()
{return this->idioma;}

Dificultad DTEstadisticaCurso::getDifficulty()
{return this->difficulty;}

float DTEstadisticaCurso::getProgress()
{return this->progress;}
