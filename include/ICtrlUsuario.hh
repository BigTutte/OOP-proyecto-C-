#ifndef ICTRLUSUARIO_H
#define ICTRLUSUARIO_H

#include "DTNotificacion.hh"
#include "DTUsuario.hh"
#include "DTEstudiante.hh"
#include "DTProfesor.hh"
#include "DTDate.hh"
#include "DTEstadisticaCursoEstudiante.hh"
#include "DTEstadisticaCurso.hh"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class ICtrlUsuario
{
    private:
    
    public:
        virtual ~ICtrlUsuario(){};
        
        //CU: ALTA DE USUARIO
        virtual void IngresarDatosUsuario(string, string, string, string) = 0;
        virtual void altarEstudiante(string, DTDate) = 0;
        virtual set<string> listarIdiomas() = 0;
        virtual void seleccionarIdiomas(set<string>) = 0;
        virtual void altarProfesor(string) = 0;

        //CU: CONSULTA DE USUARIO
        virtual set<string> listarUsuarios() = 0;
        virtual DTUsuario* seleccionarUsuario(string) = 0;

        //CU: ALTA DE IDIOMA
        virtual bool altarIdioma(string) = 0;

        //CU: CONSULTAR IDIOMAS
        virtual vector<string> consultarIdioma() = 0;

        //CU: SUSCRIBIRSE A NOTIFICACIONES
        virtual vector<string> listarIdiomasNoSuscripto(string) = 0;
        virtual void suscribirse(vector<string>) = 0;

        //CU: CONSULTA DE NOTIFICACIONES
        virtual vector<DTNotificacion> listarNotificaciones(string) = 0;

        //CU: ELIMINAR SUSCRIPCIONES
        virtual vector<string> listarIdiomasSuscripto(string) = 0;
        virtual void eliminarSuscripcion(vector<string>) = 0;

        //CU: CONSULTAR ESTADÍSTICAS
        virtual vector<string> listarEstudiantes() = 0;
        virtual vector<DTEstadisticaCursoEstudiante> listarEstadisticasE(string) = 0;
        virtual vector<string> listarProfesores() = 0;
        virtual vector<DTEstadisticaCurso> listarEstadisticasP(string) = 0;
        virtual vector<string> listarCursos() = 0;
        virtual DTEstadisticaCurso listarEstadisticaC(string) = 0;

        //CU: REALIZAR EJERCICIO
        virtual vector<string> listarCursosNoAprobados(string) = 0;
        virtual vector<string> listarEjerciciosPendientes(string) = 0;
        virtual string elegirEjercicio(string) = 0;
        virtual bool resolverProblema(string) = 0;
};

#endif
