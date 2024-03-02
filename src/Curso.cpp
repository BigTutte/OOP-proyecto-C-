#include "../include/Curso.hh"
#include "../include/CtrlCurso.hh"
#include "../include/DTInfoCurso.hh"
#include "../include/CtrlUsuario.hh"
#include "../include/Leccion.hh"
#include "../include/Inscripcion.hh"
#include "../include/DTEstadisticaCurso.hh"

#include <vector>
#include <string>

using namespace std;

Curso::Curso(string name,string desc,Dificultad diff,Idioma* leng)
{
    this->name= name;
    this->description= desc;
    this->difficulty= diff;
    this->elCursoEsDe= leng;
    this->available= false;
    this->idLeccion= 0;
}

Curso::~Curso(){}


string Curso::getName()
{return name;}

string Curso::getDescription()
{return this->description;}

Dificultad Curso::getDifficulty()
{return this->difficulty;}

int Curso::getCantLecciones()
{return this->compuestoPor.size();}

vector<int> Curso::getCantEjercicios()
{
    vector<int> v;
    for(vector<Leccion*>::iterator it = this->compuestoPor.begin();it!=this->compuestoPor.end();++it)
    {v.push_back((*it)->cantEjercicios());}

    return v;
}

int Curso::getCantEjerciciosAprobC(string nick)
{
    int cont=0;
    for(vector<Leccion*>::iterator it = this->compuestoPor.begin();it!=this->compuestoPor.end();++it)
        {cont=cont+(*it)->getCantEjerciciosAprobL(nick);}

    return cont;
}

bool Curso::isAvailable()
{return available;}

DTInfoCurso* Curso::getInfoCurso()
{
    //Profesor
    CtrlUsuario* cu= CtrlUsuario::getInstance();
    string prof= cu->getNombreProf(this->name);
    cout<<"llegue2.1.1"<<endl;

    //Lecciones
    vector<DTInfoLeccion*> infLes;
    for(vector<Leccion*>::iterator itL= this->compuestoPor.begin() ; itL!=this->compuestoPor.end() ; ++itL)
    {infLes.push_back((*itL)->getInfoLeccion());}
    cout<<"llegue2.1.2"<<endl;

    //Inscripciones
    vector<DTInfoInscripcion*> infIns;
    for(vector<Inscripcion*>::iterator itI= this->inscripciones.begin() ; itI!=this->inscripciones.end() ; ++itI)
    {infIns.push_back((*itI)->getInfoInscripcion());}
    cout<<"llegue2.1.3"<<endl;

    DTInfoCurso* res= new DTInfoCurso(this->name, this->description, this->difficulty, this->available, this->elCursoEsDe->getName(), prof, infLes, infIns);
    cout<<"llegue2.1.4"<<endl;

    return res;
}

vector<string> Curso::listLessons()
{
    vector<string> l;
    for (unsigned int i = 0; i < this->compuestoPor.size(); i++) {
        l.push_back(this->compuestoPor[i]->getTopic());
    }
    return l;
}

bool Curso::estaInscripto(string nick)
{
    vector<Inscripcion*>::iterator it= this->inscripciones.begin();
    while(it != this->inscripciones.end() && (*it)->getNickEstudiante()!=nick){++it;}

    return it!=this->inscripciones.end();
}

bool Curso::cumpleLasPrevias(string nick)
{
    bool cumplePrevia= true;
    
    vector<Curso*>::iterator it= this->previas.begin();
    while(it!=this->previas.end() && cumplePrevia)
    {
        cumplePrevia=(*it)->aproboElCurso(nick);
        ++it;
    }

    return cumplePrevia;
}

DTEstadisticaCurso Curso::getEstadisticaC()//si no hay inscriptos, progreso=-2, si no esta habilitado, progreso=-1
{
    //estEstudiante/estInscriptos
    float avanceCurso = 0;
    float progreso;
    if (this->available)
    {
        if(this->inscripciones.size()==0)
            {progreso=-2;}
        else
        {
            for(vector<Inscripcion*>::iterator it= this->inscripciones.begin();it!=this->inscripciones.end();++it)
                {avanceCurso= avanceCurso + (*it)->getPorcentajeAvanceE((*it)->getNickEstudiante());}
            
            float cantidadInscriptos = (float)(this->inscripciones.size());
            progreso = avanceCurso/cantidadInscriptos ;//multiplicar por 100 para porcentaje
        }
    }
    else
        {progreso = -1;}
    
    return DTEstadisticaCurso(this->name,this->description,this->elCursoEsDe->getName(),this->difficulty,progreso);
}

bool Curso::aproboElCurso(string nick)
{
    bool aprobo= false;

    vector<Inscripcion*>::iterator it= this->inscripciones.begin();
    while(it!=this->inscripciones.end() && (*it)->getNickEstudiante()!=nick){++it;}

    if(it!=this->inscripciones.end())
        {aprobo=(*it)->getApproved();}

    return aprobo;
}

vector<string> Curso::getEjerciciosPendientes(string nick)
{
    vector<string> v;
    int cont= 0;
    
    vector<Leccion*>::iterator it= this->compuestoPor.begin();
    while(it!=this->compuestoPor.end() && v.size()==0)
    {
        v= (*it)->getEjerciciosPendientes(nick);
        if(v.size()!=0)
            {this->idLeccion=cont;}
        ++it;
        ++cont;
        //this->idLeccion=cont++;
    }

    return v;
}

string Curso::getLetraEjercicio(string idEjercicio)
{return this->compuestoPor[this->idLeccion]->getLetraEjercicio(idEjercicio);}

bool Curso::compararSolucion(string solucion)
{return this->compuestoPor[this->idLeccion]->compararSolucion(solucion);}

bool Curso::estaCompletaLeccion(string nick)
{return this->compuestoPor[this->idLeccion]->estaCompletaLeccion(nick);}

bool Curso::estaAprobadoCurso()
{return this->compuestoPor[this->idLeccion]==this->compuestoPor.back();}
//this->compuestoPor.size()==1+this->idLeccion;}



void Curso::setIdLeccion(int id)
{this->idLeccion= id;}

void Curso::setElCursoEsDe(Idioma* idi)
{this->elCursoEsDe= idi;}

void Curso::addPrevia(Curso* c)
{
    vector<Curso*>::iterator it= this->previas.begin();
    while(it!=this->previas.end() && (*it)!=c){++it;}
    if(it==this->previas.end())
        {this->previas.push_back(c);}
}

void Curso::addLeccion(string tema,string objetivo)
{this->compuestoPor.push_back(new Leccion(tema,objetivo));}

void Curso::addEjercicioCEnLid(string descripcion,string consigna,vector<string> solucion)
{this->compuestoPor[this->idLeccion]->addEjercicioC(descripcion,consigna,solucion);}

void Curso::addEjercicioTEnLid(string descripcion,string consigna,string solucion)
{this->compuestoPor[this->idLeccion]->addEjercicioT(descripcion,consigna,solucion);}

void Curso::addInscripcion(DTDate fecha)
{this->inscripciones.push_back(new Inscripcion(this,fecha));}

bool Curso::habilitar()
{
    if (this->compuestoPor.size()>0)
    {
        vector<Leccion*>::iterator it= this->compuestoPor.begin();
        while(it!=this->compuestoPor.end() && (*it)->hayEjer()){++it;}
        
        if(it==this->compuestoPor.end())//si todas las lecciones tiene ejercicio
        {
            this->available=true;
            this->elCursoEsDe->notifyObservers(this->name);
        }
    }
    
    return this->available;
}

void Curso::deleteCourse() {
    Inscripcion* ins;
    while(0 < this->inscripciones.size())
    {
        ins = this->inscripciones[0];
        ins->unroll();
        this->inscripciones.erase(this->inscripciones.begin());
        delete ins;
    }

    Leccion* l;
    while(0 < this->compuestoPor.size())
    {
        l = this->compuestoPor[0];
        l->deleteExercices();
        this->compuestoPor.erase(this->compuestoPor.begin());
        delete l;
    }

    CtrlUsuario* cu= CtrlUsuario::getInstance();
    cu->sacarDeCursosCreados(this->name);

    CtrlCurso* cc= CtrlCurso::getInstance();
    cc->sacarDePrevias(this->name);
}

void Curso::sacarPrevia(string nCurso)
{
    vector<Curso*>::iterator it=this->previas.begin();
    while(it!=this->previas.end() && (*it)->getName()!=nCurso){++it;}
    if(it!=this->previas.end())
        {this->previas.erase(it);}
}