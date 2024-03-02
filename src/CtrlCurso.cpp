#include "../include/CtrlCurso.hh"
#include "../include/CtrlUsuario.hh"
#include "../include/Curso.hh"
#include "../include/DTInfoCurso.hh"
#include "../include/DTInfoCursoIns.hh"
#include "../include/CtrlUsuario.hh"
#include "../include/DTEstadisticaCurso.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;



CtrlCurso* CtrlCurso::instance = NULL;

CtrlCurso::CtrlCurso(){}

CtrlCurso* CtrlCurso::getInstance()
{
    if (instance == NULL)
    {
        instance = new CtrlCurso();
    }
    return instance;
}

CtrlCurso::~CtrlCurso()
{
    while(this->cursos.size()!=0)
    {
        vector<Curso*>::iterator it= this->cursos.begin();
        this->deleteCourse((*it)->getName());
    }
}

//test
/*
#include "../include/Ejercicio.hh"
void CtrlCurso::test()
{
    //busco el curso llamado Ingles para principiantes
    Curso *c;
    for (unsigned int i = 0; i < this->cursos.size(); i++)
    {
        if (this->cursos[i]->getName() == "Ingles para principiantes")
        {
            c = this->cursos[i];
            cout << "Curso encontrado" << endl;
            break;
        }
        else
        {
            cout << "Curso no encontrado" << endl;
        }
    }
    //imprimo la solucion de sus ejercicios
    vector<Leccion*> lecciones = c->getLecciones();
    for (unsigned int i = 0; i < lecciones.size(); i++)
    {
        cout << lecciones[i]->getTopic() << endl;

        vector<Ejercicio*> ejercicios = lecciones[i]->getEjercicios();
        for (unsigned int j = 0; j < ejercicios.size(); j++)
        {
            cout << "    _" << ejercicios[j]->getLetra() << "_" << endl;
            cout << "    _" << ejercicios[j]->getSolucion() << "_" << endl;
        }
    }
}
*/
//test

DTEstadisticaCurso CtrlCurso::getEstadisticaC(string nCurso)
{
    Curso *c;
    for (unsigned int i = 0; i < this->cursos.size(); i++)
    {
        if (this->cursos[i]->getName() == nCurso)
        {
            c = this->cursos[i];
            break;
        }
    }

    return c->getEstadisticaC();
}

void CtrlCurso::sacarDePrevias(string nCurso)
{
    for(vector<Curso*>::iterator it=this->cursos.begin();it!=this->cursos.end();++it)
    {
        if((*it)->getName()!=nCurso)
            {(*it)->sacarPrevia(nCurso);}
    }
}



//CU: ALTA DE CURSO:  
vector<string> CtrlCurso::listarProfesores()
{
    vector<string> v;    
    CtrlUsuario* cu = CtrlUsuario::getInstance();
    v = (cu)->getNicknameProfesores();

    return v;
}

void CtrlCurso::seleccionarProfesor(string profesor)
{
    CtrlUsuario* cu = CtrlUsuario::getInstance();
    (cu)->setUserNickname(profesor);
}

bool CtrlCurso::crearCurso(string nombreCurso,string descripcionCurso, Dificultad dificultad )
{
    vector<Curso*>::iterator it= this->cursos.begin();
    while(it!=this->cursos.end() && (*it)->getName()!=nombreCurso){++it;}
    this->cursoGuard=NULL;

    if(it==this->cursos.end())
    {
        Curso* c = new Curso(nombreCurso,descripcionCurso,dificultad, NULL);
        this->cursos.push_back(c);
        this->cursoGuard=c;

        CtrlUsuario* cu = CtrlUsuario::getInstance();
        cu->addCursosCreados_NickSave(c);
        //++it;
    }

    return this->cursoGuard!=NULL;
}

vector<string> CtrlCurso::listarIdiomas()
{
    CtrlUsuario* cu = CtrlUsuario::getInstance();

    return (cu)->getNombresIdiomas_NickSave();
}

void CtrlCurso::seleccionarIdioma(string idioma)
{
    CtrlUsuario* cu = CtrlUsuario::getInstance();
    this->cursoGuard->setElCursoEsDe(cu->getIdioma(idioma));

    //CtrlUsuario* cu = CtrlUsuario::getInstance();
    //(cu)->setIdioma(this->cursoGuard,idioma);
}

vector<string> CtrlCurso::listarCursosHabilitdos()
{
    //recorrer todos los curso y devolver un vector con los habilitados
    vector<string> v;
    for(vector<Curso*>::iterator it= this->cursos.begin() ; it!=this->cursos.end() ; ++it)
    {
        if ((*it)->isAvailable())
            {v.push_back((*it)->getName());}
    }
    return v;
}

void CtrlCurso::seleccionarPrevias(vector<string> Listaprevias)
{
    // recorrer vector strings y agregarlos a previas
    for(vector<string>::iterator nomPrev=Listaprevias.begin() ; nomPrev!=Listaprevias.end() ; ++nomPrev)
    {
        // recorrer vector cursos
        vector<Curso*>::iterator it= this->cursos.begin();
        while(it!=this->cursos.end() && (*it)->getName()!=(*nomPrev)){++it;}

        //si el nombre del curso pertenece al el vector de previas lo agrego a la lista de previas del curso guardado
        if(it!=this->cursos.end())
            {this->cursoGuard->addPrevia(*it);}
    }
}
//CU: ALTA DE CURSO.



//CU: AGREGAR LECCIÓN:
vector<string> CtrlCurso::listarCursosNoHabilitados()
{
    vector<string> cursNH;
    for(vector<Curso*>::iterator it = this->cursos.begin() ; it!=this->cursos.end() ; ++it)
    {
        if (!(*it)->isAvailable()) 
            {cursNH.push_back((*it)->getName());}
    }
    return cursNH;
}

void CtrlCurso::seleccionarCurso(string curso)
{
    vector<Curso*>::iterator it=this->cursos.begin();
    while(it!=this->cursos.end() && curso!=(*it)->getName()){++it;}
    if (it!=this->cursos.end()){this->cursoGuard=*it;}
}

void CtrlCurso::crearLeccion(string tema,string objetivo)
{
    this->cursoGuard->addLeccion(tema,objetivo);
    this->cursoGuard->setIdLeccion(this->cursoGuard->getCantLecciones()-1);
}

void CtrlCurso::crearEjercicioCompletar(string descripcion,string consigna,vector<string> solucion)
{
    this->cursoGuard->addEjercicioCEnLid(descripcion,consigna,solucion);
}

void CtrlCurso::crearEjercicioTraducir(string descripcion,string consigna,string solucion)
{
    this->cursoGuard->addEjercicioTEnLid(descripcion,consigna,solucion);
}
//CU: AGREGAR LECCIÓN.



//CU: AGREGAR EJERCICIO:
vector<string> CtrlCurso::listarLeccionesCurso(string course)
{    
    vector<string> l;
    for(unsigned int i = 0; i < this->cursos.size(); i++) {
        if(this->cursos[i]->getName() == course) {
            this->cursoGuard = this->cursos[i];
            break;
        }
    }
    return this->cursoGuard->listLessons();
}

void CtrlCurso::seleccionarLeccion(int numLec)
{
    this->cursoGuard->setIdLeccion(numLec);
}
//CU: AGREGAR EJERCICIO.



//CU: HABILITAR CURSO:
bool CtrlCurso::habilitarCurso(string curso)//al menos una lección y un ejercicio y no tiene lecciones sin ejercicios
{
    bool ret= false;
    vector<Curso*>::iterator it= this->cursos.begin();
    while(it!=this->cursos.end() && curso!=(*it)->getName()){++it;}
    if(it!=this->cursos.end())
        {ret = (*it)->habilitar();}

    return ret;
}
//CU: HABILITAR CURSO.



//CU: ELIMINAR CURSO:
void CtrlCurso::deleteCourse(string course)
{
    Curso* c;
    vector<Curso*>::iterator it= this->cursos.begin();
    while(it!=this->cursos.end() && course!=(*it)->getName()){++it;}
    if(it!=this->cursos.end())
    {
        c=(*it);
        c->deleteCourse();
        this->cursos.erase(it);
        delete c;
    }
    /*
    Curso* c;
    for (unsigned int i = 0; i < this->cursos.size(); i++) {
        if (this->cursos[i]->getName() == course) {
            c = this->cursos[i];
            c->deleteCourse();
            this->cursos.erase(this->cursos.begin() + i);
            delete c;
            break;
        }
    }*/
}
//CU: ELIMINAR CURSO.



//CU: CONSULTAR CURSO:
vector<string> CtrlCurso::listarCursos()
{
    vector<string> v;
    for(vector<Curso*>::iterator it= this->cursos.begin() ; it!=this->cursos.end() ; ++it)
        {v.push_back((*it)->getName());}

    return v;
}

DTInfoCurso* CtrlCurso::consultarCurso(string curso)
{
    DTInfoCurso* res= NULL;
    
    vector<Curso*>::iterator it= this->cursos.begin();
    while(it!=this->cursos.end() && curso!=(*it)->getName()){++it;}
    cout<<"llegue2.1"<<endl;
    if(it!=this->cursos.end())
        {res=(*it)->getInfoCurso();}
    cout<<"llegue2.2"<<endl;
    return res;
}
//CU: CONSULTAR CURSO.



//CU: INSCRIBIRSE A CURSO:
vector<DTInfoCursoIns> CtrlCurso::listarCursosParaEstudiante(string nick)
{
    CtrlUsuario* cu= CtrlUsuario::getInstance();
    cu->setUserNickname(nick);
	
    vector<DTInfoCursoIns> v;
    for(vector<Curso*>::iterator it= this->cursos.begin();it != this->cursos.end();++it)
    {
        if((*it)->isAvailable() && !(*it)->estaInscripto(nick) && (*it)->cumpleLasPrevias(nick))
        {v.push_back(DTInfoCursoIns((*it)->getName(),(*it)->getDescription(),(*it)->getDifficulty(),(*it)->getCantLecciones(),(*it)->getCantEjercicios()));}
    }

    return v;
}

void CtrlCurso::inscribirACurso(string nCurso, DTDate fecha)
{
    vector<Curso*>::iterator it= this->cursos.begin();
    while(it!=this->cursos.end() && nCurso!=(*it)->getName()){++it;}
    if(it!=this->cursos.end())
        {(*it)->addInscripcion(fecha);}
}
//CU: INSCRIBIRSE A CURSO.
