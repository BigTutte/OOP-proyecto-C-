#include "../include/DTInfoCurso.hh"

#include <vector>
#include <string>

using namespace std;

DTInfoCurso::DTInfoCurso(string nombCur, string descCur, Dificultad dif, bool habi, string nombIdi, string nombProf, vector<DTInfoLeccion*> lec, vector<DTInfoInscripcion*> ins)
{
    this->nombreCurso= nombCur;
    this->descripcionCurso= descCur;
    this->dificultad= dif;
    this->habilitado= habi;
    this->nombreIdioma= nombIdi;
    this->nombreProfesor= nombProf;
    this->lecciones= lec;
    this->inscripciones= ins;
}

DTInfoCurso::~DTInfoCurso()
{
    while(!this->lecciones.empty())
    {
        this->lecciones.erase(this->lecciones.begin());
    }
    while(!this->inscripciones.empty())
    {
        this->inscripciones.erase(this->inscripciones.begin());
    }
    //for(vector<DTInfoLeccion>::iterator it= this->lecciones.begin() ; it!=this->lecciones.end() ; ++it){(*it).~DTInfoLeccion();}
}



void DTInfoCurso::showInfoCurso()
{
    cout<<"Nombre del curso: "<<this->nombreCurso<<endl;
    cout<<endl;
    cout<<"Descripcion del curso: "<<this->descripcionCurso<<endl;
    cout<<endl;
    cout<<"Nombre del idioma: "<<this->nombreIdioma<<endl;
    cout<<endl;
    cout<<"Nombre del profesor: "<<this->nombreProfesor<<endl;
    cout<<endl;

    switch (this->dificultad)
    {
    case 0:
        cout<<"Dificultad del curso: Principiante"<<endl;
        break;
    
    case 1:
        cout<<"Dificultad del curso: Medio"<<endl;
        break;
    
    case 2:
        cout<<"Dificultad del curso: Avanzado"<<endl;
        break;
    }
    cout<<endl;

    if(this->habilitado)
        {cout<<"El curso esta habilitado"<<endl;}
    else
        {cout<<"El curso esta deshabilitado"<<endl;}
    cout<<endl;

    cout<<"Las lecciones del curso son: "<<endl;
    for(unsigned int i=0;i<this->lecciones.size();++i)
    {
        cout<<endl;
        this->lecciones[i]->showInfoLeccion();
        cout<<endl;
    }
    cout<<endl;
    cout<<"Las inscripciones del curso son: "<<endl;
    for(unsigned int i=0;i<this->inscripciones.size();++i)
    {
        cout<<endl;
        this->inscripciones[i]->showInfoInscripcion();
        cout<<endl;
    }
}