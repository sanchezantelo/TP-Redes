#include "Cliente.h"
#define PORT 8080
#define IP "127.0.0.1"

using namespace std;
Cliente::Cliente()
{
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


void Cliente::Enviar()
{
    cout<<"Escribe el mensaje a enviar: ";
    cin>>this->buffer;
    send(server, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    cout << "Mensaje enviado!" << endl;
}

void Cliente::Recibir()
{
    recv(server, buffer, sizeof(buffer), 0);
    cout << "El servidor dice: " << buffer << endl;
    memset(buffer, 0, sizeof(buffer));
}

void Cliente::CerrarSocket()
{
    closesocket(server);
    WSACleanup();
    cout << "Socket cerrado." << endl << endl;
}
