#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{
  Servidor *Server = new Servidor();
  while(Server->sesion())
  {

     Server->Recibir();
     Server->Enviar();
     if(Server->LogOutPorTimeOut()){
        Server->CerrarSocket();
        system("PAUSE");
     }

     if(strcmp(Server->buffer,"login")==0){
        Server->Login();
     }
     if(strcmp(Server->buffer,"salir")==0){
        Server->LogOut();
     }

  }
  Server->CerrarSocket();
}
