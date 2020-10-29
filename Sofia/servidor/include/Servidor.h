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
        char buffer[2048];
        time_t hora;
        char fecha[80];
        struct tm * timeinfo;
        time_t ultimaconexion;
        int  i, len, rc, on = 1;
        int  max_sd, new_sd;
        int  desc_ready, end_server = FALSE;
        int    close_conn;
        struct timeval  timeout;
        fd_set master_set, working_set;

        list<string>lstUsuarios;
        list<string>lstActividades;
        ofstream serverLog;
        ofstream clienteLog;
        Servidor();
        string Recibir();
        void Enviar(string mensaje);
        bool Login();
        bool LogOut();
        bool sesion();
        bool LogOutPorTimeOut();
        void LogServer();
        void LogCliente(string usuario);
        void CerrarSocket();
        void CargalstUsuarios();
        void ImprimirlstUsuarios();
        void ImprimirlstActividades();
        string mostrarActividades(string usuario);
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H
