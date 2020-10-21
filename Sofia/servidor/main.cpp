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

         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }

         if(server->Recibir().find("login")){
            server->Login();
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
