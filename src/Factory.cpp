#include "../include/Factory.hh"
#include "../include/CtrlCurso.hh"
#include "../include/CtrlUsuario.hh"

Factory* Factory::instance = NULL;
Factory::Factory(){}

Factory* Factory::getInstance() {
	if (Factory::instance == NULL) {
		Factory::instance = new Factory();
	}
	return Factory::instance;
}

ICtrlCurso* Factory::getICtrlCurso(){
  return CtrlCurso::getInstance();
}

ICtrlUsuario* Factory::getICtrlUsuario(){
  return CtrlUsuario::getInstance();
}

Factory::~Factory(){}
