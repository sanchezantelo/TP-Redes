#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include<ctime>
#include"list"

using namespace std;


class Servidor
{
    public:

/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/

        WSADATA WSAData;
        SOCKET server, client;
        SOCKADDR_IN serverAddr, clientAddr;
        char buffer[2048];
        bool logueado;
        time_t hora;
        char fecha[80];
        struct tm * timeinfo;
        time_t ultimaconexion;
        int puerto;
        string ip;
        list<string>lstUsuarios;
        list<string>lstActividades;
        ofstream serverLog;
        ofstream clienteLog;
        int    i, len, rc, on = 1;
   int    listen_sd, max_sd, new_sd;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   struct timeval      timeout;
   fd_set              master_set, working_set;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*  PRE: Debe existir el archivo configuraciones.txt(Conlleva ip y puerto) y credenciales(Conlleva los usuarios y contraseñas).
    POST: Servidor creado con servidor().
    ATRIBUTOS: No posee.
    RETORNO: Nueva instancia de servidor.
*/
        Servidor();

/*
    PRE: El servidor debe ser crado con servidor().
    POST: Mensaje de cliente.
    ATRIBUTOS: No posee.
    RETORNO: Mensaje del cliente.
*/
        string Recibir();

/*
    PRE: El servidor debe ser crado con servidor().
    POST: Envia el mensaje a cliente.
    ATRIBUTOS: mensaje.
    RETORNO: No posee.
*/

        void Enviar(string mensaje);
/*
    PRE: Debe existir el archivo configuraciones.txt.
    POST: Setea la ip y el puerto del servidor con los valores descriptos en el archivo.
    ATRIBUTOS: No posee.
    RETORNO: No posee.
*/

        void configuraciones();
/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir el archivo de usuarios.
    POST: Auntenticado-No Autenticado. Intentos maximos. Maximos permitidos.
    ATRIBUTOS: No posee.
    RETORNO: True si esta autenticado false si no.
*/

        bool Login();
/*
    PRE:  El servidor debe ser crado con servidor() y debe existir una conexion activa.
    POST: Devuelve true o false.
    ATRIBUTOS: No posee.
    RETORNO: True o False.
*/

        bool LogOut();

/*
    PRE:  El servidor debe ser crado con servidor().
    POST: Devuelve true o false si la sesion esta activa.
    ATRIBUTOS: No posee.
    RETORNO: True o false.
*/
        bool sesion();

/*
    PRE:  El servidor debe ser crado con servidor() y debe estar definida la variable TIMEOUT por defecto se encuentra en 2 minutos.
    POST: Verdadero o falso si el tiempo de la ultima conexion es mayor al del TIMEOUT.
    ATRIBUTOS: No posee.
    RETORNO: True o false.
*/
        bool LogOutPorTimeOut();

/*
    PRE:  El servidor debe ser crado con servidor().
    POST: Genera un archivo server.log si no existe lo crea y escribe en el archivo.
    ATRIBUTOS: mensaje.
    RETORNO: No posee.
*/
        void LogServer(string mensaje);

/*
    PRE:  El servidor debe ser crado con servidor().
    POST: Genera un archivo usuario.log si no existe lo crea y escribe en el archivo lo que pasa por el buffer.
    ATRIBUTOS: usuario.
    RETORNO: No posee.
*/

        void LogCliente(string usuario);

/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un cliente aceptado por el servidor.
    POST: Cierra el archivo de cliente y el del servidor y el SOCKET.
    ATRIBUTOS: No posee .
    RETORNO: No posee.
*/

        void CerrarSocket();

/*
    PRE:  El servidor debe ser crado con servidor().Inicializa la lista con los usuarios del txt.
    POST: Carga lo leido del archivo y lo pasa a una  lista.
    ATRIBUTOS: No posee .
    RETORNO: No posee.
*/
        void CargalstUsuarios();

/*
    PRE:  El servidor debe ser crado con servidor(). Se debe invocar al archivo usuario.log.
    POST: Retorna las actividades delimitadas por punto y coma.
    ATRIBUTOS: usuario.
    RETORNO: mensaje.
*/
        string mostrarActividades(string usuario);

/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: Setea el atributo estado en true o false.
    ATRIBUTOS: Estado true para logueado false para no logueado .
    RETORNO: No posee.
*/

        void setLogueado(bool logueado);
/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: retorna el estado.
    ATRIBUTOS: No posee.
    RETORNO: Estado true o false.
*/
        bool getLogueado();

/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: Setea el atributo puerto con int.
    ATRIBUTOS: Puerto.
    RETORNO: No posee.
*/

        void setPuerto(int puerto);

/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: retorna el puerto.
    ATRIBUTOS: No posee.
    RETORNO: int puerto.
*/
        int getPuerto();

/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: setea el atributo ip con string.
    ATRIBUTOS: ip.
    RETORNO: No posee.
*/
        void setIp(string ip);


/*
    PRE:  El servidor debe ser crado con servidor(). Debe existir un socket.
    POST: retorna el ip.
    ATRIBUTOS: No posee.
    RETORNO: int ip.
*/
        string getIp();
        virtual ~Servidor();

    protected:

    private:
};

#endif // SERVIDOR_H

