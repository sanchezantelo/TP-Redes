#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{


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

         if(server->Login()){
            server->Enviar("Ingrese usuario y contraseñia");
         }
         if(server->LogOut()){
            server->Enviar("Sesion cerrada");
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }

      }
      server->LogOut();
      server->CerrarSocket();

}
