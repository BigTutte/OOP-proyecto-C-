#include "../include/DTUsuario.hh"

#include <iostream>
#include <string>

using namespace std;

DTUsuario::DTUsuario(string nombre,string descripcion)
{
    this->nombre=nombre;
    this->descripcion=descripcion;
}

DTUsuario::~DTUsuario(){}

string DTUsuario::getNombre()
{
    return this->nombre;
}

string DTUsuario::getDescripcion()
{
    return this->descripcion;
}

