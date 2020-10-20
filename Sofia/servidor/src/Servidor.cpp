#include "Servidor.h"
#define PORT 8080
#define IP "127.0.0.1"
#define TIMEOUT 60
#include <fstream>
#include <sstream>

using namespace std;


//CONSTRUCTOR
Servidor::Servidor()
{
   this->hora = time(0);
   this->fecha = ctime(&hora);
   this->ultimaconexion= time(0);
   this->CargalstUsuarios();

 //this->ImprimirlstUsuarios();

   memset(this->buffer, 0, sizeof(this->buffer));
   WSACleanup();


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
     archivo<<"Escuchando para conexiones entrantes.";

   int clientAddrSize = sizeof(clientAddr);
   if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
     {
      cout << "Cliente conectado!" << endl;
   }
}

//DESTRUCTOR
Servidor::~Servidor()
{
    //dtor
    this->ultimaconexion= time(0);
    memset(this->buffer, 0, sizeof(this->buffer));
    client = INVALID_SOCKET;
    WSACleanup();
}

void Servidor::Login(){
   //recibir usuario y contraseña verificar credenciales
   string usuario=buffer;

   cout<<"usuario:"<<usuario.c_str()<<endl;

   for (string n : this->lstUsuarios) {
     if(n.find(usuario)==0){
       cout<<"Encontrado"<<endl;
       usuario="";
     }else{
      cout<<"No se encontro"<<endl;
     }
   }
  }

bool Servidor::sesion(){
 return client != INVALID_SOCKET;
}


bool Servidor::LogOut(){
    //this->Enviar("Sesion cerrada");
    return strcmp(this->buffer,"salir")==0;
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
   closesocket(client);
   cout << "Socket cerrado, cliente desconectado." << endl;
   this->archivo.close();
   WSACleanup();
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

void Servidor::CargalstUsuarios(){
char linea[128];
ifstream usuario;
string elemento;

usuario.open("credenciales.txt");
  while (!usuario.eof()) {
      usuario.getline(linea,sizeof(linea));
      elemento=linea;
      lstUsuarios.push_front(elemento);
  }
usuario.close();
}

void Servidor::ImprimirlstUsuarios(){
   for (string n : this->lstUsuarios){
        std::cout << n << '\n';
    }
}
