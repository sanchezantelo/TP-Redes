#include <iostream>
#include <winsock2.h>
#include <Servidor.h>
#include <Servicio.h>

using namespace std;

int CrearServicio(char * message);
bool ServicioExiste(Servicio servicio);
char* valueOfOrigen(char* origen_in);
char* valueOfTurno(char* turno_in);
void lowstr(char *s);

int main()
{
    while(true){

      Servidor *server = new Servidor();
      Servicio *serv = new Servicio(0,"",0);

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

    int CrearServicio(char * message)
    {
        /**si respuesta = 1 servicio creado con exito
        *               = 2 servicio ya existe
        *               = 3 error al crear servicio
        */
        int respuesta = 0;
        Servicio serv= Servicio(1,"",1);
        char origen[100] = "";
        int origenEntero = 0;
        char fecha[100] = "";
        string fechaString;
        char turno[100] = "";
        int turnoEntero = 0;

        string servicio = string(message);
        string servicioAGuardar;
        //se divide el mensaje en diferentes variables a traves del delimitador
        strcpy(origen, strtok(message , ";"));
        strcpy(fecha, strtok(NULL, ";"));
        strcpy(turno, strtok(NULL, ";"));

        origenEntero = atoi(valueOfOrigen(origen));
        fechaString = string(fecha);
        turnoEntero = atoi(valueOfTurno(turno));

        //setea variables del servicio
        serv.setOrigen(origenEntero);
        serv.setFecha(fechaString);
        serv.setTurno(turnoEntero);

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

    char* valueOfOrigen(char* origen_in)
    {
        /**retorna 1 si origen_in = "buenos aires"
        *          2 si origen_in = "mar del plata"
        */

        //Convierto a minuscula para no tener problema a como me llegue el mensaje
        lowstr(origen_in);
        char* keyBA = (char*)"buenos aires";
        char* keyMP = (char*)"mar del plata";
        char* respuesta = (char*)"";
        if(strcmp(keyBA, origen_in) == 0)
        {
            respuesta = (char*)"1";
        }
        else if(strcmp(keyMP, origen_in) == 0)
        {
            respuesta = (char*)"2";
        }
        return respuesta;
    }

    char* valueOfTurno(char* turno_in)
    {
        /**retorna 1 si turno_in = "maniana"
        *          2 si turno_in = "tarde"
        *          3 si turno_in = "noche"
        */

        //Convierto a minuscula para no tener problema a como me llegue el mensaje
        lowstr(turno_in);
        char* keyM = (char*)"maniana";
        char* keyT = (char*)"tarde";
        char* keyN = (char*)"noche";
        char* respuesta = (char*)"";

        if(strcmp(keyM, turno_in) == 0)
        {
            respuesta = (char*)"1";
        }
        else if(strcmp(keyT, turno_in) == 0)
        {
            respuesta = (char*)"2";
        }
        else if(strcmp(keyN, turno_in) == 0)
        {
            respuesta = (char*)"3";
        }
        return respuesta;
    }

    void lowstr(char *s)
    {
        //Convierte char a minuscula
        char *p;
        for(p = s; *p != '\0'; p++)
        {
            *p = (char) tolower(*p);
        }
    }
