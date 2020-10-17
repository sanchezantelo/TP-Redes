#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <winsock2.h>

using namespace std;


class Servidor
{
    public:
        WSADATA WSAData;
        SOCKET server, client;
        SOCKADDR_IN serverAddr, clientAddr;
        char buffer[1024];
        Servidor();
        string Recibir();
        void Enviar();
        void CerrarSocket();
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H
