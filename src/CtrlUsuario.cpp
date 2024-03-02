#include "../include/CtrlUsuario.hh"
#include "../include/Estudiante.hh"
#include "../include/Idioma.hh"
#include "../include/Profesor.hh"
#include "../include/CtrlCurso.hh"
#include "../include/Curso.hh"
#include "../include/Inscripcion.hh"
#include "../include/Usuario.hh"
#include "../include/DTDate.hh"
#include "../include/DTNotificacion.hh"
#include "../include/DTEstadisticaCursoEstudiante.hh"

#include <string>
#include <set>
#include <iterator>
#include <typeinfo>

using namespace std;


CtrlUsuario *CtrlUsuario::instance = NULL;

CtrlUsuario::CtrlUsuario(){}

CtrlUsuario *CtrlUsuario::getInstance()
{
    if (instance == NULL)
    {
        instance = new CtrlUsuario();
    }
    return instance;
}

CtrlUsuario::~CtrlUsuario()
{
    while (!this->usuarios.empty())
    {
        Usuario* u= *(this->usuarios.begin());
        this->usuarios.erase(this->usuarios.begin());
        delete u;
    }

    while (!this->idiomas.empty())
    {
        Idioma* i= *(this->idiomas.begin());
        this->idiomas.erase(this->idiomas.begin());
        delete i;
    }
}



void CtrlUsuario::setUserSave(Usuario* usu)
{this->userSave=usu;}

void CtrlUsuario::setUserNickname(string unick)
{this->userNickname=unick;}

void CtrlUsuario::addCursosCreados_NickSave(Curso* c)
{
    set<Usuario*>::iterator it=this->usuarios.begin();
    while(it!=this->usuarios.end() && (*it)->getNickname()!=this->userNickname){++it;}
    if(it!=this->usuarios.end())
    {
        Profesor* prof= dynamic_cast<Profesor*>(*it);
        prof->addCursoCreado(c);
    }
}

void CtrlUsuario::sacarDeCursosCreados(string nombreCurso)
{
    set<Usuario*>::iterator it=this->usuarios.begin();
    bool creoCurso= false;
    while(it!=this->usuarios.end() && !creoCurso)
    {
        Profesor* prof= dynamic_cast<Profesor*>(*it);
        if(prof!=NULL)
            {creoCurso= prof->creoElCurso(nombreCurso);}
        if(!creoCurso)
            {++it;}
    }

    if(it!=this->usuarios.end())
    {
        Profesor* prof= dynamic_cast<Profesor*>(*it);
        prof->removeCursoCreado(nombreCurso);
    }
}



Usuario* CtrlUsuario::getUserSave()
{return this->userSave;}

Usuario* CtrlUsuario::getUserSaveInNick()
{
    Usuario* user= NULL;
    set<Usuario*>::iterator it= this->usuarios.begin();
    while(it!=this->usuarios.end() && this->userNickname!=(*it)->getNickname()){++it;}
    
    if(it!=this->usuarios.end())
        {user=(*it);}

    return user;
}
/*
string CtrlUsuario::getNombreProf(string nombreCursoCreado)
{
    set<Usuario*>::iterator it = this->usuarios.begin();
    bool encontrado = false;

    while (it != this->usuarios.end() && !encontrado)
    {
        Profesor* current = dynamic_cast<Profesor*>(*it); // downcasting
        if (current != NULL) // si no era profesor queda NULL
            {encontrado = current->creoElCurso(nombreCursoCreado);}
        
    }

    return (*it)->getName(); // siempre lo va a encontrar porque el curso existe y fue creado por alguien
}*/
string CtrlUsuario::getNombreProf(string nombreCursoCreado)
{
    set<Usuario*>::iterator it = this->usuarios.begin();
    bool encontrado = false;

    while (it != this->usuarios.end() && !encontrado)
    {
        Profesor* current = dynamic_cast<Profesor*>(*it); // downcasting
        if (current != NULL) // si no era profesor queda NULL
            {encontrado = current->creoElCurso(nombreCursoCreado);}
        if(!encontrado)
            {++it;}
    }

    return (*it)->getName(); // siempre lo va a encontrar porque el curso existe y fue creado por alguien
}


Idioma* CtrlUsuario::getIdioma(string idi)
{
    Idioma* i=NULL;
    set<Idioma*>::iterator it=this->idiomas.begin();
    while(it!=this->idiomas.end() && (*it)->getName()!=idi){++it;}
    if(it!=this->idiomas.end())
        {i=(*it);}
    return i;
}

vector<string> CtrlUsuario::getNicknameProfesores()
{
    vector<string> v;
    for (set<Usuario*>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it)
    {
        Profesor* prof= dynamic_cast<Profesor*>(*it);
        if (prof!=NULL)
            {v.push_back(prof->getNickname());}
    }
    return v;
}

vector<string> CtrlUsuario::getNombresIdiomas_NickSave()
{
    //busco el profesor guardado en el nickname
    vector<string> v;

    set<Usuario*>::iterator it=this->usuarios.begin();
    while(it!=this->usuarios.end() && (*it)->getNickname()!=this->userNickname){++it;}
    if(it!=this->usuarios.end())
    {
        Profesor* prof= dynamic_cast<Profesor*>(*it);
        v=prof->getIdiomasConocidos();
    }

    return v;
}



//CU: ALTA DE USUARIO:
void CtrlUsuario::IngresarDatosUsuario(string nickname, string contrasena, string nombre, string descripcion)
{
    this->userNickname = nickname;
    this->userPassword = contrasena;
    this->userName = nombre;
    this->userDescription = descripcion;
}

void CtrlUsuario::altarEstudiante(string pais, DTDate fechaNac)
{this->usuarios.insert(new Estudiante(this->userNickname, this->userPassword, this->userName, this->userDescription, pais, fechaNac));}

set<string> CtrlUsuario::listarIdiomas()
{
    set<string> idi;
    for (set<Idioma*>::iterator it = this->idiomas.begin(); it != this->idiomas.end(); ++it)
        {idi.insert((*it)->getName());}
    return idi;
}

void CtrlUsuario::seleccionarIdiomas(set<string> idiomas)
{
    this->idiomasSeleccionados.clear();
    for (set<string>::iterator it = idiomas.begin(); it != idiomas.end(); ++it)
    {
        set<Idioma*>::iterator it2 = this->idiomas.begin();
        while(it2 != this->idiomas.end() && (*it) != (*it2)->getName()){++it2;}
        if (it2 != this->idiomas.end())
            {this->idiomasSeleccionados.insert((*it2));}
    }
}

void CtrlUsuario::altarProfesor(string instituto)
{this->usuarios.insert(new Profesor(this->userNickname, this->userPassword, this->userName, this->userDescription, instituto, this->idiomasSeleccionados));}
//CU: ALTA DE USUARIO.
        


//CU: CONSULTA DE USUARIO:
set<string> CtrlUsuario::listarUsuarios()
{
    set<string> usuarios;
    for (set<Usuario*>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it)
        {usuarios.insert((*it)->getNickname());}

    return usuarios;
}

DTUsuario* CtrlUsuario::seleccionarUsuario(string nickname)
{
    DTUsuario* ret= NULL;
    set<Usuario *>::iterator it = this->usuarios.begin();

    while(it!=this->usuarios.end() && (*it)->getNickname()!=nickname){++it;}

    if(it!=this->usuarios.end())
        {ret = (*it)->getDTUsuario();}

    return ret;
}
//CU: CONSULTA DE USUARIO.



//CU: ALTA DE IDIOMA:
bool CtrlUsuario::altarIdioma(string idioma)
{
    // busco el idioma
    set<Idioma*>::iterator it = this->idiomas.begin(); 
    while(it != this->idiomas.end() && (*it)->getName() != idioma){++it;} 

    // si no existe lo creo
    if (it == this->idiomas.end())
        {this->idiomas.insert(new Idioma(idioma));}

    return (it == this->idiomas.end());
}
//CU: ALTA DE IDIOMA.



//CU: CONSULTAR IDIOMAS:
vector<string> CtrlUsuario::consultarIdioma()
{
    vector<string> v;
    for (set<Idioma*>::iterator it = this->idiomas.begin(); it != this->idiomas.end(); ++it)
        {v.push_back((*it)->getName());}
    return v;
}
//CU: CONSULTAR IDIOMAS.



//CU: SUSCRIBIRSE A NOTIFICACIONES:
vector<string> CtrlUsuario::listarIdiomasNoSuscripto(string nick)
{
    vector<string> v;

    // busco el usuario
    set<Usuario *>::iterator user = this->usuarios.begin();
    while (user != this->usuarios.end() && (*user)->getNickname() != nick)
    {
        ++user;
    }

    // si lo encontré
    if (user != this->usuarios.end())
    {
        // guardo el usuario para usarlo mas adelante
        this->setUserSave((*user));

        // recorro todos los idiomas existentes
        for (set<Idioma *>::iterator idi = this->idiomas.begin(); idi != this->idiomas.end(); ++idi)
        {
            // en cada uno veo si user es un observador
            if (!((*idi)->isObserver((*user))))

                // si NO lo es lo agrego el nombre del idioma a v
                v.push_back((*idi)->getName());
        }
    }

    return v;
}

void CtrlUsuario::suscribirse(vector<string> idiomasASus)
{
    // recorro la coleccion de idiomas a los que me quiero suscribir
    for (vector<string>::iterator sus = idiomasASus.begin(); sus != idiomasASus.end(); ++sus)
    {
        // para cada uno, lo busco entre los idiomas existenes
        set<Idioma *>::iterator idi = this->idiomas.begin();
        while (idi != this->idiomas.end() && (*idi)->getName() != (*sus))
            {++idi;}

        // si lo encuentro suscribo al usuario que guardé antes
        if (idi != this->idiomas.end())
            {(*idi)->addObserver(this->userSave);}
    }
}
//CU: SUSCRIBIRSE A NOTIFICACIONES.



//CU: CONSULTA DE NOTIFICACIONES:
vector<DTNotificacion> CtrlUsuario::listarNotificaciones(string nick)
{
    vector<DTNotificacion> v;

    //busco el usuario
    set<Usuario*>::iterator user= this->usuarios.begin();
    while(user != this->usuarios.end() && (*user)->getNickname()!=nick){++user;}

    //si lo encontré
    if (user != this->usuarios.end())
        {v=(*user)->getNotificaciones();} //las guardo en v y las elimino

    return v;
}
//CU: CONSULTA DE NOTIFICACIONES.



//CU: ELIMINAR SUSCRIPCIONES:
vector<string> CtrlUsuario::listarIdiomasSuscripto(string nick)
{
    vector<string> v;

    //busco el usuario
    set<Usuario*>::iterator user= this->usuarios.begin();
    while(user != this->usuarios.end() && (*user)->getNickname()!=nick){++user;}

    //si lo encontré
    if (user != this->usuarios.end())
    {
        //guardo el usuario para usarlo mas adelante
        this->setUserSave((*user));

        //recorro todo los idiomas existenes
        for(set<Idioma*>::iterator idi=this->idiomas.begin() ; idi!=this->idiomas.end() ; ++idi)
        {
            //si es observador guardo el nombre del idioma
            if ((*idi)->isObserver(*user))
                {v.push_back((*idi)->getName());}
        }

    }

    return v;
}

void CtrlUsuario::eliminarSuscripcion(vector<string> idiomasADes)
{
    //recorro la coleccion de idiomas a los que me quiero desuscribir
    for (vector<string>::iterator des=idiomasADes.begin();des!=idiomasADes.end();++des)
    {
        //para cada uno, lo busco entre los idiomas existenes
        set<Idioma*>::iterator idi=this->idiomas.begin();
        while(idi!=this->idiomas.end() && (*idi)->getName()!=(*des)){++idi;}

        //si lo encuentro desuscribo al usuario que guardé antes
        if (idi!=this->idiomas.end())
            {(*idi)->removeObserver(this->userSave);}
    }
}
//CU: ELIMINAR SUSCRIPCIONES.



//CU: CONSULTAR ESTADÍSTICAS:
vector<string> CtrlUsuario::listarEstudiantes()
{
    vector<string> v;

    // recorro todo los usuarios existenes
    for (set<Usuario*>::iterator user = this->usuarios.begin(); user != this->usuarios.end(); ++user)
    {
        Estudiante* est= dynamic_cast<Estudiante*>(*user);
        if (est!=NULL)// si es estudiante guardo el nombre
            {v.push_back((*user)->getNickname());}
    }

    return v;
}

vector<DTEstadisticaCursoEstudiante> CtrlUsuario::listarEstadisticasE(string nick)
{
    vector<DTEstadisticaCursoEstudiante> v;

    //printf("entro a listarEstadisticasE\n");

    // busco el usuario
    set<Usuario*>::iterator user = this->usuarios.begin();
    while (user != this->usuarios.end() && (*user)->getNickname() != nick)
        {++user;}

    // si lo encontré las guardo en v
    if (user != this->usuarios.end())
    {
        Estudiante* est= dynamic_cast<Estudiante*>(*user);
        v = est->getEstadisticasE();
    }

    return v;
}

vector<string> CtrlUsuario::listarProfesores()
{
    vector<string> v;

    // recorro todo los usuarios existenes
    for (set<Usuario *>::iterator user = this->usuarios.begin(); user != this->usuarios.end(); ++user)
    {
        Profesor* est= dynamic_cast<Profesor*>(*user);
        if (est!=NULL)// si es Profesor guardo el nombre
            {v.push_back((*user)->getNickname());}
    }

    return v;
}

vector<DTEstadisticaCurso> CtrlUsuario::listarEstadisticasP(string nick)
{
    vector<DTEstadisticaCurso> v;

    // busco el usuario
    set<Usuario*>::iterator user = this->usuarios.begin();
    while (user != this->usuarios.end() && (*user)->getNickname() != nick)
        {++user;}

    // si lo encontré
    if (user != this->usuarios.end())
    {
        Profesor* prof= dynamic_cast<Profesor*>(*user);
        v = prof->getEstadisticasP();
    }

    return v;
}

vector<string> CtrlUsuario::listarCursos()
{
    CtrlCurso* cc=CtrlCurso::getInstance();

    return cc->listarCursos();
}

DTEstadisticaCurso CtrlUsuario::listarEstadisticaC(string nCurso)
{
    CtrlCurso* cc=CtrlCurso::getInstance();

    return cc->getEstadisticaC(nCurso);
}
//CU: CONSULTAR ESTADÍSTICAS.



//CU: REALIZAR EJERCICIO:
vector<string> CtrlUsuario::listarCursosNoAprobados(string nickname)
{
    vector<string> v;

    set<Usuario*>::iterator it = this->usuarios.begin();
    while(it!=this->usuarios.end() && (*it)->getNickname()!=nickname){++it;}
    
    if (it!=this->usuarios.end())// si encontro el usuario downcastear a Estudiante
    {
        Estudiante* e = dynamic_cast<Estudiante*>(*it);

        if(e!=NULL)
        {
            this->userSave = e; //Guardo el estudiante en el controlador
            v= e->getCursosNoAprobados();
        }
    }    

    return v;
}

vector<string> CtrlUsuario::listarEjerciciosPendientes(string idCurso)
{
    vector<string> v;

    Estudiante* e = dynamic_cast<Estudiante*>(this->userSave);
    v= e->getEjerciciosPendientes(idCurso);

    return v;
}

string CtrlUsuario::elegirEjercicio(string idEjercicio)
{
    Estudiante* e = dynamic_cast<Estudiante*>(this->userSave);
    
    return e->getLetraEjercicio(idEjercicio);
}

bool CtrlUsuario::resolverProblema(string solucion)
{
    Estudiante* e = dynamic_cast<Estudiante*>(this->userSave);
    
    return e->compararSolucion(solucion);
}
//CU: REALIZAR EJERCICIO.
