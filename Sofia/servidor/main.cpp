#include <iostream>
#include <winsock2.h>
#include <Servidor.h>
#include <Servicio.h>

using namespace std;

int main()
{
    while(true){
      Servidor *server = new Servidor();
      Servicio *servicio= new Servicio();

      while(server->sesion() && !server->LogOutPorTimeOut())
      {
         char message[100] = "";
         if (!server->getLogueado())
            server->Enviar("ok");
         string recibido = server->Recibir();

         if(recibido.find("login")==0){
            if(server->Login()==true){
                server->Enviar("autenticado");
                server->setLogueado(true);
            }else{
                server->Enviar("no autorizado");
                server->setLogueado(false);
                }
            }


         if(server->LogOutPorTimeOut()){
            cout<<"Expiro tiempo de sesion"<<endl;
            server->Enviar("Expiro tiempo de sesion");
            server->CerrarSocket();
            break;
            }

        if(!recibido.empty()){
            server->ActualizarTimer();
         }



         if(recibido.find("MostrarActividad")==0){
            server->Enviar(server->mostrarActividades(recibido));
         }



         if(recibido.find("G1") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            int respuesta = servicio->CrearServicio(message);
            server->Enviar(to_string(respuesta));
         }

         if(recibido.find("G2") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            string respuesta = servicio->buscarServicio(message);
            server->Enviar(respuesta);
         }
         if(recibido.find("G3") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            string respuesta = servicio->encontradoServicio(message);
            server->Enviar(respuesta);
         }
         if(recibido.find("G4") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            string respuesta = servicio->reservarAsiento(message);
            server->Enviar(respuesta);
         }

         if(server->LogOut()){
            server->Enviar("Sesion cerrada");
            server->CerrarSocket();
            break;
         }
      }
      server->~Servidor();
      servicio->~Servicio();
      }
}


