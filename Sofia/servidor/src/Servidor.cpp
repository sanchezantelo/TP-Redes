#include "Servidor.h"
#define PORT 8080
#define IP "127.0.0.1"
#define TIMEOUT 60


using namespace std;

Servidor::Servidor()
{
   this->hora = time(0);
   this->fecha = ctime(&hora);
   this->ultimaconexion= time(0);


   WSAStartup(MAKEWORD(2,0), &WSAData);
   server = socket(AF_INET, SOCK_STREAM, 0);

   serverAddr.sin_addr.s_addr = INADDR_ANY;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(PORT);

   bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
   listen(server, 0);

   cout << "Escuchando para conexiones entrantes." << endl;
   cout<<"hora local:"<<this->fecha<<endl;
   this->archivo.open("E:/Sistemas/Redes y Comunicaciones/TPRedes/TP-Redes/Sofia/servidor/logserver.txt",fstream::ate);
   this->archivo<<"Escuchando para conexiones entrantes.";

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
    char salir[1024];
    time_t hora=time(0);
    double compara=difftime(hora,this->ultimaconexion);

    this->LogServer();


   cout<<difftime(hora,this->ultimaconexion)<<endl;
   recv(client, buffer, sizeof(buffer), 0);
   strcpy(salir,this->buffer);

    if(strcmp(salir,"salir")==0 || TIMEOUT<compara){
     this->CerrarSocket();
     system("PAUSE");
    }
     memset(salir, 0, sizeof(salir));
}
//


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
   this->ultimaconexion= time(0);
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

