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
        char buffer[1024];
        Cliente();
        void Enviar(string mensaje);
        string Recibir();
        void CerrarSocket();
        void login();
        virtual ~Cliente();

    protected:

    private:
};

#endif // CLIENTE_H
