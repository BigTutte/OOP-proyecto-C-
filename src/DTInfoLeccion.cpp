#include "../include/DTInfoLeccion.hh"
#include "../include/DTInfoEjercicio.hh"

#include <vector>
#include <string>

using namespace std;

DTInfoLeccion::DTInfoLeccion(string tema, string objetivo, vector<DTInfoEjercicio*> ejercicios)
{
    this->tema= tema;
    this->objetivo= objetivo;
    this->ejercicios= ejercicios;
}

DTInfoLeccion::~DTInfoLeccion()
{
    while(!this->ejercicios.empty())
    {
        this->ejercicios.erase(this->ejercicios.begin());
    }

    //for(vector<DTInfoEjercicio*>::iterator it= this->ejercicios.begin() ; it!=this->ejercicios.end() ; ++it){delete (*it);}
}



void DTInfoLeccion::showInfoLeccion()
{
    cout<<"  Tema: "<<this->tema<<endl;
    cout<<"  Objetivo: "<<this->objetivo<<endl;
    
    cout<<"  Los ejercicios de la leccion son: "<<endl;
    for(unsigned int i=0;i<this->ejercicios.size();++i)
    {
        this->ejercicios[i]->showInfoEjercicio();
        cout<<endl;
    }
}
