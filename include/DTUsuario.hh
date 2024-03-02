#ifndef DTUSUARIO_H
#define DTUSUARIO_H

#include <iostream>
#include <string>

using namespace std;

class DTUsuario {
    private:
        string nombre;
        string descripcion;

    public:
        DTUsuario(string,string);
        virtual ~DTUsuario() = 0;
        string getNombre();
        string getDescripcion();
};

#endif