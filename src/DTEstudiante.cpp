#include "../include/DTEstudiante.hh"
#include "../include/DTUsuario.hh"
#include "../include/DTDate.hh"

using namespace std;

DTEstudiante::DTEstudiante(string nombre, string descripcion, DTDate fecha,string pais) : DTUsuario(nombre, descripcion)
{
    this->fechaNacimiento=fecha;
    this->paisResidencia=pais;
}

DTDate DTEstudiante::getFechaNacimiento()
{
    return this->fechaNacimiento;
}

string DTEstudiante::getPaisResidencia()
{
    return this->paisResidencia;
}   

