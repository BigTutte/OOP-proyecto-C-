#ifndef ICTRLCURSO_H
#define ICTRLCURSO_H

#include "DTInfoCurso.hh"
#include "DTEstadisticaCurso.hh"
#include "DTEstadisticaCursoEstudiante.hh"
#include "Leccion.hh"
#include "Ejercicio.hh"
#include "DTInfoCursoIns.hh"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ICtrlCurso 
{
    public:
        virtual ~ICtrlCurso(){};

        //CU: ALTA DE CURSO
        virtual vector<string> listarProfesores() = 0;
        virtual void seleccionarProfesor(string) = 0;
        virtual bool crearCurso(string,string,Dificultad) = 0;
        virtual vector<string> listarIdiomas() = 0;
        virtual void seleccionarIdioma(string) = 0;
        virtual vector<string> listarCursosHabilitdos() = 0;
        virtual void seleccionarPrevias(vector<string>) = 0;
        //virtual void crearLeccion(string,string) = 0;
        //virtual void crearEjercicioCompletar(string,string,vector<string>) = 0;
        //virtual void crearEjercicioTraducir(string,string,string) = 0;

        //CU: AGREGAR LECCIÓN
        virtual vector<string> listarCursosNoHabilitados() = 0;
        virtual void seleccionarCurso(string) = 0;
        virtual void crearLeccion(string,string) = 0;
        virtual void crearEjercicioCompletar(string,string,vector<string>) = 0;
        virtual void crearEjercicioTraducir(string,string,string) = 0;

        //CU: AGREGAR EJERCICIO
        //virtual vector<string> listarCursosNoHabilitados() = 0;
        virtual vector<string> listarLeccionesCurso(string) = 0;
        virtual void seleccionarLeccion(int) = 0;
        //virtual void crearEjercicioCompletar(string,string,vector<string>) = 0;
        //virtual void crearEjercicioTraducir(string,string,string) = 0;

        //CU: HABILITAR CURSO
        //virtual vector<string> listarCursosNoHabilitados() = 0;
        virtual bool habilitarCurso(string) = 0;

        //CU: ELIMINAR CURSO
        //virtual vector<string> listarCursos() = 0;
        virtual void deleteCourse(string) = 0;

        //CU: CONSULTAR CURSO
        virtual vector<string> listarCursos() = 0;
        virtual DTInfoCurso* consultarCurso(string) = 0; //hay que llamar su destructor despues de usarlo

        //CU: INSCRIBIRSE A CURSO
        virtual vector<DTInfoCursoIns> listarCursosParaEstudiante(string) = 0;
        virtual void inscribirACurso(string,DTDate) = 0;
};

#endif
