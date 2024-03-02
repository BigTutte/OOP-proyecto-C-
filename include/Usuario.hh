#ifndef USUARIO_H
#define USUARIO_H

#include "IObserver.hh"
#include "DTNotificacion.hh"
#include "DTUsuario.hh"

#include <string>
#include <vector>

using namespace std;

class IObserver;

class Usuario : public IObserver
{
    private:
        string nickname;
        string password;
        string name;
        string description;

        vector<DTNotificacion> notificaciones;

    public:
        Usuario(string, string, string, string);
        virtual ~Usuario() = 0;

        string getNickname();
        string getName();
        string getDescription();
        vector<DTNotificacion> getNotificaciones();//devuelve las notificaciones y las elimina
        virtual DTUsuario* getDTUsuario() = 0;
        
        void notify(string,string) override;
};

#endif
