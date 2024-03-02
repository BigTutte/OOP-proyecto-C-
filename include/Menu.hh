#ifndef MENU_H
#define MENU_H

#include <iostream>

using namespace std;

enum State {START, LOAD, STATE0, OP1, OP2, OP3, OP4, OP5, OP6, OP7, OP8, OP9, OP10, OP11, OP12, OP13, OP14, OP15, OP16};

class Factory;
class ICtrlUsuario;
class ICtrlCurso;

class Menu {
    private:
        int option;
        bool exit;
        State state;
    public:
        Menu();

        void menuLimits();
        void loadSystem(bool&);
        void startMenu();
        void showMenu();
        void loader();
        void selectOption();
        void executeOption();
        void AltaUsuario();
        void ConsultaUsuario();
        void AltaIdioma();
        void ConsultarIdiomas();
        void AltaCurso();
        void AgregarLeccion();
        void AgregarEjercicio();
        void HabilitarCurso();
        void EliminarCurso();
        void ConsultarCurso();
        void InscribirseACurso();
        void RealizarEjercicio();
        void ConsultarEstadisticas();
        void SuscribirseANotificaciones();
        void ConsultaNotificaciones();
        void EliminarSuscripciones();
        void showOptions();
        
        ~Menu();
};

#endif