#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <winsock2.h>

using namespace std;

class Cliente
{
    public:
        WSADATA WSAData;
        SOCKET server;
        SOCKADDR_IN addr;
        bool ingresa;
        bool sesion;
        char buffer[2048];
        string userName;
        Cliente();
        void Enviar(string mensaje);
        string Recibir();
        void setSesion(bool sesion);
        bool getSesion();
        string getuserName();
        void setuserName(string userName);
        void CerrarSocket();
        virtual ~Cliente();

    protected:

    private:
};

#endif // CLIENTE_H
