#include "../include/Traduccion.hh"
#include "../include/DTInfoEjercicioT.hh"

#include <string>

using namespace std;


Traduccion::Traduccion(string description,string phrase,string translation) : Ejercicio(description)
{
    this->phraseToTranslate = phrase;
    this->translation = translation;
}

Traduccion::~Traduccion(){}



DTInfoEjercicio* Traduccion::getInfoEjercicio()
{return new DTInfoEjercicioT(this->getDescription(), this->phraseToTranslate, this->translation);}

string Traduccion::getLetra()
{return this->phraseToTranslate;}

bool Traduccion::compararSolucion(string solucion)
{return solucion==this->translation;}
