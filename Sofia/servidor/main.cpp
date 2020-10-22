#include <iostream>
#include <winsock2.h>
#include <Servidor.h>
#include <Servicio.h>

using namespace std;

int CrearServicio(char * message);
bool ServicioExiste(Servicio servicio);

int main()
{
    while(true){

      Servidor *server = new Servidor();
      Servicio *serv = new Servicio(0,"",0);

      while(server->sesion() && !server->LogOutPorTimeOut())
      {

         char message[100] = "";
         server->Enviar("ok");

         if(server->Recibir().find("login")==0){
            if(server->Login()==true){
                server->Enviar("autenticado");
            }else{
                server->Enviar("no autorizado");
                server->CerrarSocket();
                break;
            }
         }

         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }



         if(server->Recibir().find("G1") == 0){
            strcpy(message, server->Recibir().erase(0,3).c_str());
            int respuesta = CrearServicio(message);
            server->Enviar(to_string(respuesta));
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

int CrearServicio(char * message)
{
    /**si respuesta = 1 servicio creado con exito
    *               = 2 servicio ya existe
    *               = 3 error al crear servicio
    */
    int respuesta = 0;
    Servicio serv= Servicio(1,"",1);
    char origen[5] = "";
    char fecha[15] = "";
    char turno[5] = "";

    string servicioAGuardar;

    //se divide el mensaje en diferentes variables a traves del delimitador
    strcpy(origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(turno, strtok(NULL, ";"));


    //setea variables del servicio
    serv.setOrigen(atoi(origen));
    serv.setFecha(string(fecha));
    serv.setTurno(atoi(turno));

    char nombreArchivo[] = "servicios.txt";
    fstream servicios;

    servicios.open(nombreArchivo, fstream::in | fstream::out | fstream::app);

    //Si no existe, arroja error
    if(!servicios)
    {
        cout<< "No se pudo abrir el archivo.";
        respuesta = 3;
    }
    //Siempre lo crea con el fstream pero por algun error se pone arriba, y aca sigue la logica
    else{
        cout<<"Se encontro archivo: "<<nombreArchivo<<endl;

        //Variable para usar de parametro en el archivo y buscar si ya existe un servicio con el parametro de entrada
        string storedServicio;

        //to-do comparar si ya existe un servicio
        if(ServicioExiste(serv))
        {
        respuesta = 2;
        }

        else
        {
        servicioAGuardar = serv.crearServicio();
        servicios<<servicioAGuardar<<endl;
        respuesta = 1;
        }

    }
    return respuesta;
}
//to-do
bool ServicioExiste(Servicio servicio)
{
    return false;
}
