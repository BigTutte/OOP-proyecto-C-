
#include "../include/IObserver.hh"
#include "../include/Usuario.hh"
#include "../include/Idioma.hh"
#include "../include/DTNotificacion.hh"

#include <string>

using namespace std;


Usuario::Usuario(string nickname, string password, string name, string description)
{
    this->nickname = nickname;
    this->password = password;
    this->name = name;
    this->description = description;
}

Usuario::~Usuario(){}



string Usuario::getNickname()
{return this->nickname;}

string Usuario::getName()
{return this->name;}

string Usuario::getDescription()
{return this->description;}

vector<DTNotificacion> Usuario::getNotificaciones()
{
    vector<DTNotificacion> v;
    for(vector<DTNotificacion>::iterator it=this->notificaciones.begin() ; it!=this->notificaciones.end() ; ++it)
        {v.push_back(DTNotificacion((*it).getNIdioma(),(*it).getNCurso()));}

    this->notificaciones.clear();

    return v;
}

void Usuario::notify(string idi,string cur)
{this->notificaciones.push_back(DTNotificacion(idi,cur));}
