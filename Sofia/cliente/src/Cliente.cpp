#include "Cliente.h"
#define PORT 8080
#define IP "127.0.0.1"
#include<winsock2.h>
#include <Servicio.h>

using namespace std;

Cliente::Cliente()
{
    memset(this->buffer, 0, sizeof(this->buffer));
    cout<<"Conectando al servidor..."<<endl<<endl;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Conectado al Servidor!" << endl;    //ctor
}

Cliente::~Cliente()
{
    //dtor
}


void Cliente::Enviar(string mensaje)
{
    char status[1024];
    //cin>>this->buffer;
    strcpy(status,mensaje.c_str());
    send(server,status, sizeof(status), 0);
}

string Cliente::Recibir()
{
    string mensaje;
    char status[1024];
    recv(server, buffer, sizeof(buffer), 0);
    strcpy(status,buffer);
    //strcpy(status,mensaje.c_str());
    mensaje = status;
    return mensaje;
}

void Cliente::CerrarSocket()
{
    closesocket(server);
    WSACleanup();
    cout << "Socket cerrado." << endl << endl;
}
