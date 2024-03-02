#ifndef CTRLCURSO_H
#define CTRLCURSO_H

#include "ICtrlCurso.hh"
#include "Curso.hh"
#include "DTInfoCurso.hh"
#include "DTInfoCursoIns.hh"
#include "DTEstadisticaCurso.hh"


#include <vector>

using namespace std;

class CtrlCurso : public ICtrlCurso {
    private:
        static CtrlCurso* instance;
        CtrlCurso();

        vector<Curso*> cursos;
        Curso* cursoGuard;

    public:
        static CtrlCurso* getInstance();
        ~CtrlCurso();


        DTEstadisticaCurso getEstadisticaC(string);
        void sacarDePrevias(string);


        
        //CU: ALTA DE CURSO
        vector<string> listarProfesores() override;
        void seleccionarProfesor(string) override;
        bool crearCurso(string,string,Dificultad) override;
        vector<string> listarIdiomas() override;
        void seleccionarIdioma(string) override;
        vector<string> listarCursosHabilitdos() override;
        void seleccionarPrevias(vector<string>) override;
        //void crearLeccion(string,string) override;
        //void crearEjercicioCompletar(string,string,vector<string>) override;
        //void crearEjercicioTraducir(string,string,string) override;

        //CU: AGREGAR LECCIÓN
        vector<string> listarCursosNoHabilitados() override;
        void seleccionarCurso(string) override;
        void crearLeccion(string,string) override;
        void crearEjercicioCompletar(string,string,vector<string>) override;
        void crearEjercicioTraducir(string,string,string) override;

        //CU: AGREGAR EJERCICIO
        //vector<string> listarCursosNoHabilitados() override;
        vector<string> listarLeccionesCurso(string) override;
        void seleccionarLeccion(int) override;
        //void crearEjercicioCompletar(string,string,vector<string>) override;
        //void crearEjercicioTraducir(string,string,string) override;

        //CU: HABILITAR CURSO
        //vector<string> listarCursosNoHabilitados() override;
        bool habilitarCurso(string) override;

        //CU: ELIMINAR CURSO
        //vector<string> listarCursos() override;
        void deleteCourse(string) override;

        //CU: CONSULTAR CURSO
        vector<string> listarCursos() override;
        DTInfoCurso* consultarCurso(string) override; //hay que llamar su destructor despues de usarlo

        //CU: INSCRIBIRSE A CURSO
        vector<DTInfoCursoIns> listarCursosParaEstudiante(string) override;
        void inscribirACurso(string,DTDate) override;

        //test
        //void test();
};

#endif
