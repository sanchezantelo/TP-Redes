#include "Servidor.h"
#define PORT 8080
#define IP "127.0.0.1"
#include<ctime>


using namespace std;

Servidor::Servidor()
{
   WSAStartup(MAKEWORD(2,0), &WSAData);
   server = socket(AF_INET, SOCK_STREAM, 0);

   serverAddr.sin_addr.s_addr = INADDR_ANY;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(PORT);

   bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
   listen(server, 0);

   cout << "Escuchando para conexiones entrantes." << endl;
   this->file.open("E:/Sistemas/Redes y Comunicaciones/TPRedes/TP-Redes/Sofia/servidor/logserver.txt",fstream::ate);
   this->file<<"Escuchando para conexiones entrantes.";

   int clientAddrSize = sizeof(clientAddr);
   if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
     {
      cout << "Cliente conectado!" << endl;
   }
}

Servidor::~Servidor()
{
    //dtor
}

string Servidor::Recibir()
{
   time_t now = time(0);
   char* dt = ctime(&now);

   recv(client, buffer, sizeof(buffer), 0);
   this->LogServer();
   //
}

void Servidor::Enviar()
{
   //cout<<"Escribe el mensaje a enviar: ";
   char status [1024]="Recibido";
   //cin>>this->buffer;
   send(client, status, sizeof(buffer), 0);
   //memset(buffer, 0, sizeof(buffer));
   //cout << "Mensaje enviado!" << endl;
}

void Servidor::CerrarSocket()
{
   closesocket(client);
   cout << "Socket cerrado, cliente desconectado." << endl;
   this->file.close();
}

void Servidor::LogServer()
{


   cout<<this->buffer<<"\n";
   this->file<<this->buffer<<"\n";
   //memset(buffer, 0, sizeof(buffer));

}
