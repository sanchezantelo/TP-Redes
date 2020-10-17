#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <winsock2.h>

class Cliente
{
    public:
        WSADATA WSAData;
        SOCKET server;
        SOCKADDR_IN addr;
        char buffer[1024];
        Cliente();
        void Enviar();
        void Recibir();
        void CerrarSocket();
        void login();
        virtual ~Cliente();

    protected:

    private:
};

#endif // CLIENTE_H
