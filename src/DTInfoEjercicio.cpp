#include "../include/DTInfoEjercicio.hh"

#include <string>

using namespace std;

DTInfoEjercicio::DTInfoEjercicio(string descripcion,string consigna)
{
    this->descripcion= descripcion;
    this->consigna= consigna;
}

DTInfoEjercicio::~DTInfoEjercicio(){}



string DTInfoEjercicio::getDescripcion()
{return this->descripcion;}

string DTInfoEjercicio::getConsigna()
{return this->consigna;}
