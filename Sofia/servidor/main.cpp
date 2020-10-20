#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{
    while(true){

      Servidor *server = new Servidor();
      while(server->sesion() && !server->LogOutPorTimeOut())
      {

         server->Recibir();
         server->Enviar("OK");
         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }

         if(server->Recibir().find("login")){
            server->Login();
            server->Enviar("Ingrese usuario y contrasenia");
         }
         if(server->LogOut()){
            server->Enviar("Sesion cerrada");
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }

      }
      server->~Servidor();
      }

}
