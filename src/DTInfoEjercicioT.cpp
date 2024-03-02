#include "../include/DTInfoEjercicioT.hh"

#include <string>

using namespace std;

DTInfoEjercicioT::DTInfoEjercicioT(string descripcion,string consigna,string solucion):DTInfoEjercicio(descripcion,consigna)
{
    this->solucion= solucion;
}



void DTInfoEjercicioT::showInfoEjercicio()
{
    cout<<endl;
    cout<<"    Tipo: Traduccion"<<endl;
    cout<<"    Descripcion: "<<this->getDescripcion()<<endl;
    cout<<"    Consigna: "<<this->getConsigna()<<endl;
    cout<<"    Solucion: "<<this->solucion<<endl;
}
