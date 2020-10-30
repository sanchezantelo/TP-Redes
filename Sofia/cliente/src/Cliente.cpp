#include "Cliente.h"
#define PORT 8080
#define IP "127.0.0.1"
#include<winsock2.h>
#include <Servicio.h>

using namespace std;

Cliente::Cliente()
{
    this->sesion=false;
    memset(this->buffer, 0, sizeof(this->buffer));
    cout<<"Conectando al servidor..."<<endl<<endl;
    int status;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    status=connect(server, (SOCKADDR *)&addr, sizeof(addr));

    if (status == SOCKET_ERROR) {
        wprintf(L"No se pudo conectar con el servidor status: %ld\n", WSAGetLastError());
        status = closesocket(this->server);
        exit(0);
        system("PAUSE");
        WSACleanup();


    }else{
    cout << "Conectado al Servidor!" << endl;    //ctor
    }
}


Cliente::~Cliente()
{
 this->sesion=false;
}


void Cliente::Enviar(string mensaje)
{
    memset(this->buffer,0,sizeof(this->buffer));
    send(server, mensaje.c_str(), mensaje.size(), 0);
}

string Cliente::Recibir()
{
    string mensaje;
    recv(server, this->buffer, sizeof(this->buffer), 0);
    mensaje=this->buffer;
    return mensaje;
}

void Cliente::CerrarSocket()
{
    closesocket(server);
    WSACleanup();
    cout << "\nSesion cerrada" << endl << endl;
}

bool Cliente::getSesion(){
    if(server == INVALID_SOCKET || server == SOCKET_ERROR){
        this->sesion=false;
    }
return this->sesion;
}

void Cliente::setSesion(bool sesion){
this->sesion=sesion;
}

string Cliente::getuserName(){
return this->userName;
}
void Cliente:: setuserName(string userName){
this->userName=userName;
}
