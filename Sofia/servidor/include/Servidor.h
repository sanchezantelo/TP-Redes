#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include<ctime>


using namespace std;


class Servidor
{
    public:
        WSADATA WSAData;
        SOCKET server, client;
        SOCKADDR_IN serverAddr, clientAddr;
        char buffer[1024];
        time_t now;
        char* dt;
        ofstream file;
        Servidor();
        string Recibir();
        void Enviar();
        void LogServer();
        void CerrarSocket();
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H
