#include "../include/Idioma.hh"
#include "../include/Usuario.hh"

#include <string>

using namespace std;


Idioma::Idioma(string name)
{this->name= name;}

Idioma::~Idioma(){}



string Idioma::getName()
{return this->name;}

bool Idioma::isObserver(IObserver* obs)
{
    //busco el usuario en la coleccion de usuarios del idioma
    vector<IObserver*>::iterator it= this->observers.begin();
    while(it!=this->observers.end() && (*it)!=obs){++it;}

    //retorno si lo encontré o no
    return it!=this->observers.end();
}



void Idioma::addObserver(IObserver* obs)
{this->observers.push_back(obs);}

void Idioma::removeObserver(IObserver* obs)
{
    vector<IObserver*>::iterator it = this->observers.begin();
    while(it!=this->observers.end() && (*it)!=obs){++it;} //busco el observador a eliminar
    
    if (it!=this->observers.end())
        {this->observers.erase(it);} //si lo encontré, lo elimino de la lista de observadores
}
    
void Idioma::notifyObservers(string newCourse)
{
    for(vector<IObserver*>::iterator it = this->observers.begin() ; it!=this->observers.end() ; ++it)
        {(*it)->notify(this->name,newCourse);}
}
