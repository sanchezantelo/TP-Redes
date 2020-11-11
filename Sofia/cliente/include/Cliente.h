#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <winsock2.h>

using namespace std;

class Cliente
{
    public:

/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/

        WSADATA WSAData;
        SOCKET server;
        SOCKADDR_IN addr;
        bool ingresa;
        bool sesion;
        char buffer[2048];
        string userName;
        string ip;
        int puerto;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
    PRE: La instancia Cliente no debe haberse creado (contructor) ni destruido(destructor)con anterioridad.
    POST: Cliente creado con Cliente.
    ATRIBUTOS: No posee.
    RETORNO: No aplica.
*/
        Cliente();
/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Cliente creado con Cliente.
    ATRIBUTOS: ip, puerto.
    RETORNO: No aplica.
*/
        Cliente(string ip, int puerto);

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Devuelve true o false si se pudo o no conectar con el servidor.
    ATRIBUTOS: No posee.
    RETORNO: true o false.
*/
        bool conectar();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Setea el atributo puerto con int.
    ATRIBUTOS: puerto.
    RETORNO: No posee.
*/
        void setPuerto(int puerto);

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Retorna el puerto.
    ATRIBUTOS: No posee.
    RETORNO: puerto.
*/
        int getPuerto();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Setea el atributo ip con int.
    ATRIBUTOS: ip.
    RETORNO: No posee.
*/
        void setIp(string ip);

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Retorna el ip.
    ATRIBUTOS: No posee.
    RETORNO: ip.
*/
        string getIp();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Envia el mensaje al servidor.
    ATRIBUTOS: mensaje.
    RETORNO: No posee.
*/
        void Enviar(string mensaje);

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Recibe el mensaje de servidor.
    ATRIBUTOS: No posee.
    RETORNO: mensaje.
*/
        string Recibir();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Setea el atributo sesion con bool.
    ATRIBUTOS: sesion.
    RETORNO: No posee.
*/
        void setSesion(bool sesion);
/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Retorna la sesion.
    ATRIBUTOS: No posee.
    RETORNO: true false.
*/
        bool getSesion();
/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Retorna userName.
    ATRIBUTOS: No posee.
    RETORNO: userName.
*/
        string getuserName();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Setea el atributo userName con string.
    ATRIBUTOS: userName.
    RETORNO: No posee.
*/
        void setuserName(string userName);

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Cierra el socket con el servidor.
    ATRIBUTOS: No posee.
    RETORNO: No posee.
*/
        void CerrarSocket();

/*
    PRE: La instancia Cliente debe haberse creado (constructor) pero no debe estar destruida (destructor).
    POST: Compara mensaje que recibe del servidor.
    ATRIBUTOS: No posee.
    RETORNO: true o false.
*/
        bool timeOut();
        virtual ~Cliente();

    protected:

    private:
};

#endif // CLIENTE_H
