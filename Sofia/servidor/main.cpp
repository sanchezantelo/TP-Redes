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
         server->Enviar("");
         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }

         if(server->Recibir().find("login")){
            if(server->Login()==true){
                server->Enviar("autenticado");
            }else{
                server->Enviar("no autorizado");
                server->CerrarSocket();
                break;
            }
         }

         if(server->LogOut()){
            server->Enviar("Sesion cerrada");
            server->CerrarSocket();
            system("PAUSE");
            break;
         }

      }
      server->~Servidor();
      }

}
