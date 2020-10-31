#include "Cliente.h"
#include<winsock2.h>
#include <Servicio.h>

using namespace std;

Cliente::Cliente(string ip, int puerto)
{
    this->ip=ip;
    this->puerto=puerto;
    this->sesion=false;
    memset(this->buffer, 0, sizeof(this->buffer));
}

Cliente::Cliente(){
}

bool Cliente::conectar(){
    bool conectado=false;
    cout<<"Conectando al servidor..."<<endl<<endl;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->puerto);
    int status=connect(server, (SOCKADDR *)&addr, sizeof(addr));

    if (status == SOCKET_ERROR) {
        cout<<"No se pudo conectar con el servidor: "<<this->ip<<", Puerto: "<<to_string(this->puerto)<<", Codigo de error: "<<WSAGetLastError()<<endl;
        status = closesocket(this->server);
        system("PAUSE");
        WSACleanup();


    }else{
    cout << "Conectado al Servidor!" << endl;    //ctor
    conectado=true;
    }
}


Cliente::~Cliente()
{
 this->sesion=false;
}

void Cliente::setPuerto(int puerto){
    this->puerto=puerto;
}
int Cliente::getPuerto(){
    return this->puerto;
}
void Cliente::setIp(string ip){
    this->ip=ip;
}
string Cliente::getIp(){
    return this->ip;
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
