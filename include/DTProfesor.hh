#ifndef DTPROFESOR_H
#define DTPROFESOR_H

#include "DTUsuario.hh"

#include <vector>

using namespace std;

class DTProfesor : public DTUsuario {
    private:
        string instituto;
        vector<string> idiomas;

    public:
        DTProfesor(string,string,string,vector<string>);
        ~DTProfesor(){};
        string getInstituto();
        vector<string> getIdiomas();
};

#endif