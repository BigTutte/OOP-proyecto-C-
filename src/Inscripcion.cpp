#include "../include/Inscripcion.hh"
#include "../include/Curso.hh"
#include "../include/CtrlUsuario.hh"
#include "../include/DTDate.hh"
#include "../include/DTInfoInscripcion.hh"
#include "../include/DTEstadisticaCursoEstudiante.hh"

#include <vector>

using namespace std;


Inscripcion::Inscripcion(DTDate fecha)
{
    this->inscriptionDate= fecha;
    this->approved= false;
    this->curso= NULL;
	this->estudiante= NULL;
}

Inscripcion::Inscripcion(Curso* c, DTDate fecha)
{
	CtrlUsuario* cu= CtrlUsuario::getInstance();
	
	this->inscriptionDate= fecha;
	this->approved= false;
	this->curso= c;
	this->estudiante= dynamic_cast<Estudiante*>(cu->getUserSaveInNick());
	this->estudiante->addInscripcion(this);
}



DTInfoInscripcion* Inscripcion::getInfoInscripcion()
{return new DTInfoInscripcion(this->estudiante->getName(),this->inscriptionDate);}

string Inscripcion::getNickEstudiante()
{return this->estudiante->getNickname();}

DTEstadisticaCursoEstudiante Inscripcion::getStudentStatistic(string nick)
{
    printf("entro a getStudentStatistic\n");
    return DTEstadisticaCursoEstudiante(this->curso->getName(),this->getPorcentajeAvanceE(nick));}

float Inscripcion::getPorcentajeAvanceE(string nick)
{
    //printf("entro a getPorcentajeAvanceE\n");
    int cantEjer=0;
    vector<int> cantEjers= this->curso->getCantEjercicios();
    for(vector<int>::iterator it= cantEjers.begin();it != cantEjers.end();++it)
        {cantEjer=cantEjer+(*it);}
    int cantEjerAprob= this->curso->getCantEjerciciosAprobC(nick);    
    //printf("cantEjer: %d\n",cantEjer);
    //printf("cantEjerciciosAprobC: %d\n",cantEjerAprob);       
    float porcentaje=((float)cantEjerAprob / (float)cantEjer)*100;//multiplicar por 100 para porcentaje
    //printf("porcentaje: %f\n",porcentaje); 
    return porcentaje;//multiplicar por 100 para porcentaje
}

bool Inscripcion::getApproved()
{return this->approved;}

string Inscripcion::getNombreCurso()
{return this->curso->getName();}

vector<string> Inscripcion::getEjerciciosPendientes(string nick)
{return this->curso->getEjerciciosPendientes(nick);}

string Inscripcion::getLetraEjercicio(string idEjercicio)
{return this->curso->getLetraEjercicio(idEjercicio);}

bool Inscripcion::compararSolucion(string solucion)
{return this->curso->compararSolucion(solucion);}

bool Inscripcion::estaCompletaLeccion(string nick)
{return this->curso->estaCompletaLeccion(nick);}

bool Inscripcion::estaAprobadoCurso()
{return this->curso->estaAprobadoCurso();}



void Inscripcion::setApproved(bool apr)
{this->approved= apr;}



void Inscripcion::unroll() {
    this->estudiante->eraseInscription(this);
}
