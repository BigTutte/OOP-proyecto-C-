#include "../include/DTNotificacion.hh"

#include <string>

using namespace std;

DTNotificacion::DTNotificacion(string idioma,string curso)
{
    this->nCurso=curso;
    this->nIdioma=idioma;
}

string DTNotificacion::getNIdioma()
{return this->nIdioma;}

string DTNotificacion::getNCurso()
{return this->nCurso;}

DTNotificacion::~DTNotificacion(){}

/*
DataNotificacion* DTNotificacion::getDataNotificacion() {
    DataNotificacion* d = 0;
    return d;
}
*/