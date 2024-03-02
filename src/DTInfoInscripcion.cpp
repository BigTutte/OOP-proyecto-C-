#include "../include/DTInfoInscripcion.hh"
#include "../include/DTDate.hh"

#include <string>

using namespace std;

DTInfoInscripcion::DTInfoInscripcion(string nombreEst,DTDate date)
{
    this->nombreEstudiante= nombreEst;
    this->fechaInsc= date;    
}



void DTInfoInscripcion::showInfoInscripcion()
{
    cout<<"  Nombre del estudiante inscripto: "<<this->nombreEstudiante<<endl;
    cout<<"  Fecha de inscripcion: ";
    this->fechaInsc.showDate();
}
