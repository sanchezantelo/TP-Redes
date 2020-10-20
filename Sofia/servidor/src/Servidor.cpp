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
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   this->hora = time(0);
   this->serverLog.open("serverlog.txt");

   this->ultimaconexion= time(0);
   this->CargalstUsuarios();

 //this->ImprimirlstUsuarios();
   //fechalog=this->fecha;
   //cout<<fechalog.substr(11,8)+"...";

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

   int clientAddrSize = sizeof(clientAddr);
   if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
     {
      cout << "Cliente conectado!" << endl;
      this->LogServer();
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
   //recibir usuario y contrase�a verificar credenciales
   string usuario=buffer;
   boolean encontrado=false;

   cout<<"usuario:"<<usuario.c_str()<<endl;
//while(i<size){
   for (string n : this->lstUsuarios) {
     if(n.find(usuario)==0){
       encontrado=true;
       this->LogCliente(usuario.substr(0,5)); //MODIFICAR LONGITUD
       usuario="";
     }
   }
if(encontrado==true){
    cout<<"encontrado"<<endl;


}else{
cout<<"no encontrado"<<endl;
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
   this->serverLog.close();
   this->clienteLog.close();
   WSACleanup();
}

void Servidor::LogServer()
{
   string fechalog="";
   //ACTUALIZA LA HORA DEL SERVIDOR
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   strftime(this->fecha,80,"%Y-%m-%d_%H:%M",this->timeinfo);
   fechalog=this->fecha;
   cout<<fechalog<<" :"<<this->buffer<<"\n";
   this->serverLog<<fechalog<<": ==========================="<<"\n";
   this->serverLog<<fechalog<<":        Inicia Servidor     "<<"\n";
   this->serverLog<<fechalog<<": ==========================="<<"\n";
   this->serverLog<<fechalog<<this->buffer<<"\n";
}

void Servidor::LogCliente(string usuario)
{
 string fechalog="";

   this->clienteLog.open(usuario+".txt");
   //ACTUALIZA LA HORA DEL SERVIDOR
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   strftime(this->fecha,80,"%Y-%m-%d_%H:%M",this->timeinfo);
   fechalog=this->fecha;
   cout<<fechalog<<" :"<<this->buffer<<"\n";
   this->clienteLog<<fechalog<<": ==========================="<<"\n";
   this->clienteLog<<fechalog<<":        Inicia Sesion       "<<"\n";
   this->clienteLog<<fechalog<<": ==========================="<<"\n";
   this->clienteLog<<fechalog<<this->buffer<<"\n";
}

void Servidor::CargalstUsuarios(){
char linea[128];
ifstream credenciales;
string usuario;

credenciales.open("credenciales.txt");
  while (!credenciales.eof()) {
      credenciales.getline(linea,sizeof(linea));
      usuario=linea;
      lstUsuarios.push_front(usuario);
  }
credenciales.close();
}

void Servidor::ImprimirlstUsuarios(){
   for (string usuario : this->lstUsuarios){
        cout << usuario << '\n';
    }
}
