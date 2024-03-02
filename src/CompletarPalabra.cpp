#include "../include/CompletarPalabra.hh"
#include "../include/DTInfoEjercicioC.hh"
#include "../include/DTInfoEjercicio.hh"
#include "../include/Ejercicio.hh"

#include <vector>
#include <string>

using namespace std;


CompletarPalabra::CompletarPalabra(string descripcion, string consigna,vector<string> solucion):Ejercicio(descripcion)
{
    this->phraseToComplete= consigna;
    this->solution= solucion;
}

CompletarPalabra::~CompletarPalabra(){}



DTInfoEjercicio* CompletarPalabra::getInfoEjercicio()
{return new DTInfoEjercicioC(this->getDescription(), this->phraseToComplete, this->solution);}

string CompletarPalabra::getLetra()
{return this->phraseToComplete;}

bool CompletarPalabra::compararSolucion(string solucion)
{
    bool b= true;
    vector<string> sol;
    string elem;
    for(unsigned int i= 0 ; i<solucion.size() ; ++i)
    {
        if(solucion[i]!=',')
            {elem += solucion[i];}
        else
        {
            sol.push_back(elem);
            elem.clear();
        }
        
        if(i+1==solucion.size())
        {
            sol.push_back(elem);
            elem.clear();
        }
    }

    if(this->solution.size()==sol.size())
    {
        unsigned int i= 0;
        while(i<sol.size() && b)
        {
            b=this->solution[i]==sol[i];
            ++i;
        }
    }
    else
        {b=false;}

    return b;
}
