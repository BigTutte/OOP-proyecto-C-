#ifndef FACTORY_H
#define FACTORY_H

#include "ICtrlCurso.hh"
#include "ICtrlUsuario.hh"

class ICtrlCurso;
class ICtrlUsuario;

class Factory{
    private:
        static Factory* instance;
        Factory();
    public:
      static Factory* getInstance();

      ICtrlCurso* getICtrlCurso();
      ICtrlUsuario* getICtrlUsuario();

      ~Factory();
};

#endif
