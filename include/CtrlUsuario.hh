#ifndef CTRLUSUARIO_H
#define CTRLUSUARIO_H

#include "ICtrlUsuario.hh"
#include "Usuario.hh"
#include "Idioma.hh"
#include "Curso.hh"
#include "DTUsuario.hh"
#include "DTDate.hh"
#include "DTEstadisticaCursoEstudiante.hh"
#include "DTEstadisticaCurso.hh"

#include <set>
#include <string>

using namespace std;
 
class CtrlUsuario : public ICtrlUsuario
{
    private:
        static CtrlUsuario *instance;
        CtrlUsuario();

        set<Usuario*> usuarios;
        set<Idioma*> idiomas;

        Usuario* userSave;
        string userNickname;
        string userPassword;
        string userName;
        string userDescription;
        set<Idioma*> idiomasSeleccionados;

    public:
        static CtrlUsuario *getInstance();
        ~CtrlUsuario();//debe usarse luego de usar el destructor de CtrlCurso

        void setUserSave(Usuario*);
        void setUserNickname(string);
        void addCursosCreados_NickSave(Curso*);
        void sacarDeCursosCreados(string);

        Usuario* getUserSave();
        Usuario* getUserSaveInNick();
        string getNombreProf(string nombreCursoCreado); // devuelve el nombre del profesor que creó el curso nombreCursoCreado
        Idioma* getIdioma(string);
        vector<string> getNicknameProfesores();
        vector<string> getNombresIdiomas_NickSave();

        //CU: ALTA DE USUARIO
        void IngresarDatosUsuario(string, string, string, string) override;
        void altarEstudiante(string, DTDate) override;
        set<string> listarIdiomas() override;
        void seleccionarIdiomas(set<string>) override;
        void altarProfesor(string) override;

        //CU: CONSULTA DE USUARIO
        set<string> listarUsuarios() override;
        DTUsuario* seleccionarUsuario(string) override;

        //CU: ALTA DE IDIOMA
        bool altarIdioma(string) override;

        //CU: CONSULTAR IDIOMAS
        vector<string> consultarIdioma() override;

        //CU: SUSCRIBIRSE A NOTIFICACIONES
        vector<string> listarIdiomasNoSuscripto(string) override;
        void suscribirse(vector<string>) override;

        //CU: CONSULTA DE NOTIFICACIONES
        vector<DTNotificacion> listarNotificaciones(string) override;

        //CU: ELIMINAR SUSCRIPCIONES
        vector<string> listarIdiomasSuscripto(string) override;
        void eliminarSuscripcion(vector<string>) override;

        //CU: CONSULTAR ESTADÍSTICAS
        vector<string> listarEstudiantes() override;
        vector<DTEstadisticaCursoEstudiante> listarEstadisticasE(string) override;
        vector<string> listarProfesores() override;
        vector<DTEstadisticaCurso> listarEstadisticasP(string) override;
        vector<string> listarCursos() override;
        DTEstadisticaCurso listarEstadisticaC(string) override;

        //CU: REALIZAR EJERCICIO
        vector<string> listarCursosNoAprobados(string) override;
        vector<string> listarEjerciciosPendientes(string) override;
        string elegirEjercicio(string) override;
        bool resolverProblema(string) override;
};

#endif
