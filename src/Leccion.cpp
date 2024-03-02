#include "../include/Leccion.hh"
#include "../include/CompletarPalabra.hh"
#include "../include/Traduccion.hh"
#include "../include/DTInfoLeccion.hh"
#include "../include/Ejercicio.hh"

#include <vector>
#include <string>

using namespace std;


Leccion::Leccion(string tema, string objetivo){
    this->topic= tema;
    this->objective= objetivo;
}

Leccion::~Leccion(){}



bool Leccion::hayEjer()
{return this->compuestaPor.size()>0;}

DTInfoLeccion* Leccion::getInfoLeccion()
{
    vector<DTInfoEjercicio*> infEje;
    for(vector<Ejercicio*>::iterator it= this->compuestaPor.begin() ; it!=this->compuestaPor.end() ; ++it)
        {infEje.push_back((*it)->getInfoEjercicio());}

    return new DTInfoLeccion(this->topic,this->objective,infEje);
}

string Leccion::getTopic()
{return this->topic;}

int Leccion::cantEjercicios()
{return this->compuestaPor.size();}

int Leccion::getCantEjerciciosAprobL(string nick)
{
    int cont=0;
    for(vector<Ejercicio*>::iterator it= this->compuestaPor.begin() ; it!=this->compuestaPor.end() ; ++it)
    {
        if((*it)->estaAprobado(nick))
            {cont++;}
    }

    return cont;
}

vector<string> Leccion::getEjerciciosPendientes(string nick)
{
    vector<string> v;
    
    for(vector<Ejercicio*>::iterator it= this->compuestaPor.begin() ; it!=this->compuestaPor.end() ; ++it)
    {
        if((*it)->estaPendiente(nick))
            {v.push_back((*it)->getDescription());}
    }

    return v;
}

string Leccion::getLetraEjercicio(string idEjercicio)
{
    string letra;
    vector<Ejercicio*>::iterator it= this->compuestaPor.begin();
    while(it!=this->compuestaPor.end() && (*it)->getDescription()!=idEjercicio){++it;}
    
    if(it!=this->compuestaPor.end())
    {
        letra= (*it)->getLetra();
        this->ejerSave = (*it);
    }

    return letra;
}

bool Leccion::compararSolucion(string solucion)
{
    bool esCorrecto= this->ejerSave->compararSolucion(solucion);

    if(esCorrecto)
        {this->ejerSave->setRealizado();}

    return esCorrecto;
}

bool Leccion::estaCompletaLeccion(string nick)
{
    bool lecComp= true;

    vector<Ejercicio*>::iterator it= this->compuestaPor.begin();
    while(it!=this->compuestaPor.end() && lecComp)
    {
        lecComp= (*it)->estaRealizado(nick);
        ++it;
    }

    return lecComp;
}



void Leccion::addEjercicioC(string descripcion,string consigna,vector<string> solucion)
{this->compuestaPor.push_back(new CompletarPalabra(descripcion,consigna,solucion));}

void Leccion::addEjercicioT(string descripcion,string consigna,string solucion)
{this->compuestaPor.push_back(new Traduccion(descripcion,consigna,solucion));}

void Leccion::deleteExercices() 
{
    Ejercicio* ex;
    while(0 < this->compuestaPor.size())
    {
        ex = this->compuestaPor[0];
        this->compuestaPor.erase(this->compuestaPor.begin());
        delete ex;
    }
}
