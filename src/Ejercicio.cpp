#include "../include/Ejercicio.hh"
#include "../include/Inscripcion.hh"
#include "../include/CtrlUsuario.hh"

#include <string>

using namespace std;


Ejercicio::Ejercicio(string descripcion)
{this->description= descripcion;}



string Ejercicio::getDescription()
{return this->description;}

bool Ejercicio::estaAprobado(string nick)
{
    vector<Inscripcion*>::iterator it=this->ejercicioAprobado.begin();
    while(it!=this->ejercicioAprobado.end() && (*it)->getNickEstudiante()!=nick){++it;}

    return it!=this->ejercicioAprobado.end();
}

bool Ejercicio::estaPendiente(string nick)
{
    vector<Inscripcion*>::iterator it=this->ejercicioAprobado.begin();
    while(it!=this->ejercicioAprobado.end() && (*it)->getNickEstudiante()!=nick){++it;}

    return it==this->ejercicioAprobado.end();
}

bool Ejercicio::estaRealizado(string nick)
{
    vector<Inscripcion*>::iterator it=this->ejercicioAprobado.begin();
    while(it!=this->ejercicioAprobado.end() && (*it)->getNickEstudiante()!=nick){++it;}

    return it!=this->ejercicioAprobado.end();
}



void Ejercicio::setRealizado()
{
    CtrlUsuario* cu= CtrlUsuario::getInstance();
    Estudiante* e= dynamic_cast<Estudiante*>(cu->getUserSave());

    this->ejercicioAprobado.push_back(e->getInsSave());
}
