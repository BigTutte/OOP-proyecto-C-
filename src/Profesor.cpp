#include "../include/Profesor.hh"
#include "../include/Idioma.hh"
#include "../include/Curso.hh"
#include "../include/DTUsuario.hh"
#include "../include/DTProfesor.hh"
//#include "../include/CtrlCurso.hh"

#include <vector>
#include <string>
#include <set>

using namespace std;


Profesor::Profesor(string nickname, string password, string name, string description, string instituto, set<Idioma *> idiomas) : Usuario(nickname, password, name, description)
{
    this->instituto = instituto;
    this->idiomas = idiomas;
}

/*
Profesor::~Profesor()
{
    CtrlCurso* cc= CtrlCurso::getInstance();
    while (!this->cursosCreados.empty())
    {
        cc->deleteCourse(this->cursosCreados.back()->getName());
    }
}
*/



bool Profesor::creoElCurso(string nombreCurso)
{
    vector<Curso*>::iterator it= this->cursosCreados.begin();
    while (it!=this->cursosCreados.end() && (*it)->getName()!=nombreCurso){++it;}
    
    return it!=this->cursosCreados.end(); //si no llegó al final lo encontró
}

vector<string> Profesor::getIdiomasConocidos()
{
    vector<string> v;
    for(set<Idioma*>::iterator it= this->idiomas.begin();it!=this->idiomas.end();++it)
        {v.push_back((*it)->getName());}
        
    return v;
}

DTUsuario* Profesor::getDTUsuario()
{return new DTProfesor(this->getName(),this->getDescription(),this->instituto,this->getIdiomasConocidos());}

vector<DTEstadisticaCurso> Profesor::getEstadisticasP()
{
    vector<DTEstadisticaCurso> v;
    
    for(vector<Curso*>::iterator it= this->cursosCreados.begin();it!=this->cursosCreados.end();++it)
        {v.push_back((*it)->getEstadisticaC());}
    
    return v;
}



void Profesor::addCursoCreado(Curso* c)
{this->cursosCreados.push_back(c);}

void Profesor::removeCursoCreado(string nombreCurso)
{
    vector<Curso*>::iterator it= this->cursosCreados.begin();
    while (it!=this->cursosCreados.end() && (*it)->getName()!=nombreCurso){++it;}

    if(it!=this->cursosCreados.end())
        {this->cursosCreados.erase(it);}
}