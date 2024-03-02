#ifndef DTNOTIFICACION_H
#define DTNOTIFICACION_H

#include <iostream>
#include <string>

using namespace std;

class DTNotificacion{
    private:
        string nIdioma,nCurso;
    public:
        DTNotificacion(string,string);
        ~DTNotificacion();

        string getNIdioma();
        string getNCurso();
};

#endif