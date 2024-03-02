#include "../include/DTInfoEjercicioC.hh"

#include <vector>
#include <string>

using namespace std;

DTInfoEjercicioC::DTInfoEjercicioC(string descripcion,string consigna,vector<string> solucion):DTInfoEjercicio(descripcion,consigna)
{
    this->solucion= solucion;
}



void DTInfoEjercicioC::showInfoEjercicio()
{
    cout<<endl;
    cout<<"    Tipo: Completar Palabra"<<endl;
    cout<<"    Descripcion: "<<this->getDescripcion()<<endl;
    cout<<"    Consigna: "<<this->getConsigna()<<endl;

    string elem;
    for(unsigned int i = 0 ; i < this->solucion.size() ; ++i)
    {
        elem += solucion[i];
        if(i+1!=solucion.size())
            {elem += ",";}
    }
    
    cout<<"    Solucion: "<<elem<<endl;
}
