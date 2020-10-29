#include "Servidor.h"
#define PORT 8080
#define IP "127.0.0.1"
#define TIMEOUT 60
#include <fstream>
#include <sstream>
#include<ostream>

using namespace std;

//CONSTRUCTOR
Servidor::Servidor()
{
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   this->hora = time(0);
   this->ultimaconexion= time(0);
   this->CargalstUsuarios();
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
      strcpy(this->buffer,"cliente conectado");
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


bool Servidor::Login(){
   //recibir usuario y contrase�a verificar credenciales
   string usuario=this->buffer;
   string contrasenia;
   bool autenticado=false;
   string fechalog=this->fecha;

   cout<<fechalog<<" :"<<usuario<<endl;
   contrasenia=usuario.substr(usuario.find_first_of(";",usuario.find_last_of(";")),usuario.find_last_of(";")); //contrase�a
   usuario.replace(usuario.find_first_of(";",usuario.find_last_of(";")),usuario.find_last_of(";"),"");
   usuario.replace(0,usuario.find_first_of(";"),""); //corta login
   cout<<fechalog<<" :"<<usuario.replace(0,1,"")<<";"<<contrasenia.replace(0,1,"")<<endl; //longitud 12 usuario

   for (string user : this->lstUsuarios) {
     if(user.compare(usuario+";"+contrasenia)==0 && usuario.length()!=12){
       autenticado=true;
      this->LogCliente(usuario.replace(0,0,"")); //MODIFICAR LONGITUD
     }
   }
return autenticado;
}

bool Servidor::LogOut(){
    //this->Enviar("Sesion cerrada");
    return strcmp(this->buffer,"salir;")==0;
}

bool Servidor::LogOutPorTimeOut(){
    int opcion=1;
    time_t hora=time(0);
    double compara=difftime(hora,this->ultimaconexion);
    return (TIMEOUT<compara);
}


bool Servidor::sesion(){
 return client != INVALID_SOCKET;
}

//RECIBIR
string Servidor::Recibir()
{
    string mensaje;
    recv(client, this->buffer, sizeof(this->buffer), 0);
    mensaje = this->buffer;
    return mensaje;
}

//ENVIAR
void Servidor::Enviar(string mensaje)
{
   memset(this->buffer,0,sizeof(this->buffer));
   send(client, mensaje.c_str(), mensaje.size(), 0);
}

void Servidor::CerrarSocket()
{

   string fechalog="";

   this->Enviar("Sesion cerrada");
   closesocket(client);
   strcpy(this->buffer,"Socket cerrado, cliente desconectado.");
//ACTUALIZA LA HORA DEL SERVIDOR
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   strftime(this->fecha,80,"%Y-%m-%d_%H:%M",this->timeinfo);
   fechalog=this->fecha;
   this->clienteLog<<fechalog<<": "<<this->buffer<<"\n";
   this->serverLog <<fechalog<<": "<<this->buffer<<"\n";
   this->LogServer();
   this->serverLog.close();
   this->clienteLog.close();
   WSACleanup();
}


//LOG SERVER
void Servidor::LogServer()
{
   string fechalog="";
   this->serverLog.open("serverlog.log",fstream::app);
   //ACTUALIZA LA HORA DEL SERVIDOR
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   strftime(this->fecha,80,"%Y-%m-%d_%H:%M",this->timeinfo);
   fechalog=this->fecha;
   cout<<fechalog<<" :"<<this->buffer<<"\n";
   this->serverLog<<fechalog<<": ==========================="<<"\n";
   this->serverLog<<fechalog<<":        Inicia Servidor     "<<"\n";
   this->serverLog<<fechalog<<": ==========================="<<"\n";
   this->serverLog<<fechalog<<": "<<this->buffer<<"\n";

}

//LOG CLIENTE
void Servidor::LogCliente(string usuario)
{
 string fechalog="";

   this->clienteLog.open(usuario+".log",fstream::app);
   //ACTUALIZA LA HORA DEL SERVIDOR
   time (&this->hora);
   this->timeinfo = localtime (&this->hora);
   strftime(this->fecha,80,"%Y-%m-%d_%H:%M",this->timeinfo);
   fechalog=this->fecha;
   cout<<fechalog<<" :"<<this->buffer<<"\n";
   this->clienteLog<<fechalog<<": ==========================="<<"\n";
   this->clienteLog<<fechalog<<":        Inicia Sesion       "<<"\n";
   this->clienteLog<<fechalog<<": ==========================="<<"\n";
   this->clienteLog<<fechalog<<": "<<this->buffer<<"\n";

}


//ADMINISTRACION USUARIOS
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

string Servidor:: mostrarActividades(string usuario){
char linea[150];
ifstream archivo;

string cliente,filename;

filename=usuario.substr(usuario.find_first_of(";",usuario.find_last_of(";")),usuario.find_last_of(";"))+".log";
cout<<filename<<endl;

archivo.open(filename.replace(0,1,"").c_str(),ios::in);
  if(archivo.fail()){
    cout<<"No se pudo abrir el archivo"<<endl;
  }

  while (!archivo.eof()) {
      archivo.getline(linea,sizeof(linea));
      cliente=cliente;linea;
      //this->lstActividades.push_front(cliente);

  }
archivo.close();
return cliente;
}

void Servidor::ImprimirlstActividades(){
   for (string cliente : this->lstActividades){
        cout << cliente << '\n';
    }
}
