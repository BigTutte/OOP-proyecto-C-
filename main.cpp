#include "../include/Include.hh"

int main() {

    Factory* factory = Factory::getInstance();
    ICtrlCurso* ctrlCurso = factory->getICtrlCurso();
    ICtrlUsuario* ctrlUsuario = factory->getICtrlUsuario();

    Menu* menu = new Menu();
    menu->showMenu();

    //CtrlCurso* ctrlCurso2 = CtrlCurso::getInstance();
    //ctrlCurso2->test();
    
    delete menu;
    delete factory;
    delete ctrlCurso;
    delete ctrlUsuario;
    
    return 0;

}
