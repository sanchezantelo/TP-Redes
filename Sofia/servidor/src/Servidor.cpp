#include "Servidor.h"
#define PORT 8080
#define IP "127.0.0.1"
#define TIMEOUT 60


using namespace std;

Servidor::~Servidor()
{
    //dtor
}

Servidor::Servidor()
{
   this->hora = time(0);
   this->fecha = ctime(&hora);
   this->ultimaconexion= time(0);
   memset(this->buffer, 0, sizeof(this->buffer));


   WSAStartup(MAKEWORD(2,0), &WSAData);
   server = socket(AF_INET, SOCK_STREAM, 0);

   serverAddr.sin_addr.s_addr = INADDR_ANY;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(PORT);

   bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
   listen(server, 0);

   cout << "Escuchando para conexiones entrantes." << endl;
   cout<<"Hora local: "<<this->fecha<<endl;
   this->archivo.open("E:/Sistemas/Redes y Comunicaciones/TPRedes/TP-Redes/Sofia/servidor/logserver.txt",fstream::ate);
   this->archivo<<"Escuchando para conexiones entrantes.";

   int clientAddrSize = sizeof(clientAddr);
   if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
     {
      cout << "Cliente conectado!" << endl;
   }
}

void Servidor::Login(){
   this->Enviar("Ingrese usuario y contrase�ia");
}

bool Servidor::sesion(){
 return !strcmp(this->buffer,"salir")==0;
}


void Servidor::LogOut(){
    this->Enviar("Sesion cerrada");
}

bool Servidor::LogOutPorTimeOut(){
    int opcion=1;
    time_t hora=time(0);
    double compara=difftime(hora,this->ultimaconexion);
    return (TIMEOUT<compara);
}

string Servidor::Recibir()
{
    string mensaje;
    char status[1024];
    this->LogServer();
    recv(client, buffer, sizeof(buffer), 0);
    strcpy(status,this->buffer);
    strcpy(status,mensaje.c_str());
    return mensaje;
}
//


void Servidor::Enviar(string mensaje)
{
   char status[1024];
   strcpy(status,mensaje.c_str());
   send(client, status, sizeof(status), 0);
}

void Servidor::CerrarSocket()
{
   this->Enviar("Sesion cerrada");
   this->ultimaconexion= time(0);
   memset(this->buffer, 0, sizeof(this->buffer));
   closesocket(client);
   cout << "Socket cerrado, cliente desconectado." << endl;
   this->archivo.close();
}

void Servidor::LogServer()
{

   this->hora = time(0);
   this->fecha=ctime(&hora);
   cout<<this->buffer<<"\n";
   this->archivo<<this->fecha;
   this->archivo<<this->buffer<<"\n";
   //memset(buffer, 0, sizeof(buffer));
}


