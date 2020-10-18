#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{

    while(true)
    {
      Servidor *server = new Servidor();
      while(server->sesion())
      {

         server->Recibir();
         server->Enviar("OK");
         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            system("PAUSE");
         }

         if(strcmp(server->buffer,"login")==0){
            server->Login();
         }
         if(strcmp(server->buffer,"salir")==0){
            server->LogOut();
            server->CerrarSocket();
            system("PAUSE");
         }

      }
      server->LogOut();
      server->CerrarSocket();
     }
}
