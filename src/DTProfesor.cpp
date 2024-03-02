#include "../include/DTProfesor.hh"
#include "../include/DTUsuario.hh"

#include <vector>

using namespace std;

DTProfesor::DTProfesor(string nombre, string descripcion, string instituto, vector<string> idiomas) : DTUsuario(nombre, descripcion)
{
    this->instituto=instituto;
    this->idiomas=idiomas;
}

string DTProfesor::getInstituto()
{
    return this->instituto;
}

vector<string> DTProfesor::getIdiomas()
{
    return this->idiomas;
}
