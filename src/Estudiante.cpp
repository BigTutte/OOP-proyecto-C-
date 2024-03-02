#include "../include/Estudiante.hh"
#include "../include/DTDate.hh"
#include "../include/DTUsuario.hh"
#include "../include/DTEstudiante.hh"
#include "../include/Inscripcion.hh"

#include <string>
#include <set>
#include <vector>

using namespace std;

Estudiante::Estudiante(string nickname, string password, string name, string description, string country, DTDate date) : Usuario(nickname, password, name, description)
{
    this->country = country;
    this->date = date;
    this->insSave= NULL;
}

/*
Estudiante::~Estudiante()
{
    while(!this->inscripciones.empty())
    {
        delete this->inscripciones.back();
        this->inscripciones.pop_back();
    }
}
*/



void Estudiante::addInscripcion(Inscripcion* ins)
{this->inscripciones.push_back(ins);}



DTUsuario* Estudiante::getDTUsuario()
{return new DTEstudiante(this->getName(),this->getDescription(),this->date,this->country);}

vector<DTEstadisticaCursoEstudiante> Estudiante::getEstadisticasE()
{
    //printf("entro a getEstadisticasE\n");
    vector<DTEstadisticaCursoEstudiante> estadisticas;
    for (vector<Inscripcion*>::iterator it = this->inscripciones.begin(); it != this->inscripciones.end(); ++it)
        {estadisticas.push_back((*it)->getStudentStatistic((*it)->getNickEstudiante()));}

    return estadisticas;
}

vector<string> Estudiante::getCursosNoAprobados()
{
    vector<string> v;
    
    for(vector<Inscripcion*>::iterator it=this->inscripciones.begin();it!=this->inscripciones.end();++it)
    {
        if(!(*it)->getApproved())
            {v.push_back((*it)->getNombreCurso());}
    }
    
    return v;
}

vector<string> Estudiante::getEjerciciosPendientes(string nCurso)
{
    vector<string> v;

    vector<Inscripcion*>::iterator it = this->inscripciones.begin();
    while(it!=this->inscripciones.end() && (*it)->getNombreCurso()!=nCurso){++it;}

    if(it!=this->inscripciones.end())
    {
        this->insSave=(*it);
        v= (*it)->getEjerciciosPendientes(this->getNickname());
    }

    return v;
}

string Estudiante::getLetraEjercicio(string idEjercicio)
{return this->insSave->getLetraEjercicio(idEjercicio);}

Inscripcion* Estudiante::getInsSave()
{return this->insSave;}



void Estudiante::eraseInscription(Inscripcion* inscription) {
    for(unsigned int i = 0; i < this->inscripciones.size(); i++) {
        if(this->inscripciones[i] == inscription) {//hay que ver si es valido esto, pero creo que no por el tema de la identidad
            this->inscripciones.erase(this->inscripciones.begin() + i);
            break;
        }
    }
}

bool Estudiante::compararSolucion(string solucion)
{
    bool esCorrecto= this->insSave->compararSolucion(solucion);
    if(esCorrecto)
    {
        bool leccionCompleta= this->insSave->estaCompletaLeccion(this->getNickname());
        if(leccionCompleta)
        {
            bool aprobado= this->insSave->estaAprobadoCurso();
            if(aprobado)
            {
                this->insSave->setApproved(true);
            }
        }
    }

    return esCorrecto;
}
