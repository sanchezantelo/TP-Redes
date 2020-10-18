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
        time_t hora;
        char* fecha;
        time_t ultimaconexion;
        ofstream archivo;
        Servidor();
        string Recibir();
        void Enviar(string mensaje);
        void Login();
        void LogOut();
        bool sesion();
        bool LogOutPorTimeOut();
        void LogServer();
        void CerrarSocket();
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H
