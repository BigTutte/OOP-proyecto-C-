#include "../include/DTEstadisticaCursoEstudiante.hh"

#include <string>

using namespace std;

DTEstadisticaCursoEstudiante::DTEstadisticaCursoEstudiante(string name,float progreso)
{
    this->course=name;
    this->progress=progreso;
}



string DTEstadisticaCursoEstudiante::getCourse()
{return this->course;}

float DTEstadisticaCursoEstudiante::getProgress()
{return this->progress;}
