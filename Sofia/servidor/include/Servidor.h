#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include<ctime>
#include"list"

using namespace std;


class Servidor
{
    public:
        WSADATA WSAData;
        SOCKET server, client;
        SOCKADDR_IN serverAddr, clientAddr;
        char buffer[1024];
        time_t hora;
        char fecha[80];
        struct tm * timeinfo;
        time_t ultimaconexion;
        list<string>lstUsuarios;
        ofstream serverLog;
        Servidor();
        string Recibir();
        void Enviar(string mensaje);
        void Login();
        bool LogOut();
        bool sesion();
        bool LogOutPorTimeOut();
        void LogServer();
        void LogCliente();
        void CerrarSocket();
        void CargalstUsuarios();
        void ImprimirlstUsuarios();
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H
