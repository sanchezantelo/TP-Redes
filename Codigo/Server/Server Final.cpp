#include <stdio.h>
#include <winsock2.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "../Funciones/Funciones.h"
#define PORT 54321
#define IP "127.0.0.1"

using namespace std;

bool Login(char* usuario, char* password);

int main(int arg, char** argv){
    //INICIALIZAR UN SOCKET
    SOCKET sockServer = crearSocket();
    //-----------------------------------------------------------------------------------------------------
    //CREAR ESTRUCTURA Y UNIR LOS DATOS DEL SOCKET CON BIND
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; //Le decimos que use ipv4.
    sin.sin_addr.s_addr = inet_addr(IP); //Direccion ip de la cual escuchar� el servidor.
    sin.sin_port = htons(PORT); //Puerto del cual escuchara el servidor
    memset(sin.sin_zero,0,sizeof(sin.sin_zero)); //RELLENO ( arreglo de 8 bytes que SIEMPRE debera ser llenado con ceros por cuestiones problematicas...)

    bind(sockServer,(struct sockaddr*)&sin, sizeof(sin)); //Al socket sockServer le agregamos datos (ip y puerto)
    //----------------------------------------------------------------------------------------------------------
    //EMPEZAR A ESCUCHAR LISTEN
    listen(sockServer,0);

    //BUCLE INFINITO PARA ACEPTAR INFINITOS USUARIOS
    while(true){
        //bucle de un cliente en concreto, cuando el cliente ponga cerrar sesion o haga 3 intentos
        //fallidos o pasen 2 min, entonces se saldra del bucle.
        bool desconectar = false;
        while(!desconectar){
            struct sockaddr_storage addrstorage; //storage es para guardar los datos del cliente que se va a conectar.
            int length = sizeof(addrstorage); //ya que no sabes el tama�o de la conexion del cliente (ipv4, ipv6 u otro), necesitamos hacer un sizeof.
            system("cls");
            printf("Esperando a un cliente...");
            SOCKET sockClient = accept(sockServer,(struct sockaddr*)&addrstorage,&length); //"en el socket sockServer, acepto la conexion proveniente de un cliente X
            //y voy a guardar los datos del cliente en addrstorage. Luego les devuelvo un socket del cliente para que puedan comunicarse entre ustedes que llamamos sockClient"
            system("cls");
            printf("Cliente Encontrado!.\n");

            //RECIBIMOS USUARIO Y CONTRASE�A:
            char user[1000] = "", pass[1000] = "", respuesta[2] = "";
            bool salir = false;
            int numeroIntentos = 0;
            //Se sale del bucle cuando el cliente ingrese bien el usuario y contrase�a o halla fallado 3 veces
            do {
                printf("\nEsperando Ingreso de usuario y contrase%ca...", 164);
                memset(user,0,1000);
                memset(pass,0,1000);
                recv(sockClient,user,sizeof(user),0); //recibo el usuario que escribio el cliente y lo guardo en user.
                recv(sockClient,pass,sizeof(pass),0); //recibo la contrase�a que escribio el cliente y lo guardo en pass.

                //COMPROBAMOS EL USUARIO Y CONTRASE�A EN credenciales.txt:
                if( Login(user, pass) )
                {
                    cout<<"\nLogin Correcto. Cliente Conectado."<<endl;
                    strcpy(respuesta, "OK");
                    enviar(sockClient,respuesta, 2); //envio el texto "OK" al cliente
                    salir = true;
                }
                else
                {
                    cout << "\nUsuario o contrase\xA4"<< "a incorrectos." << endl;
                    strcpy(respuesta, "NO");
                    enviar(sockClient,respuesta, 2); //envio el texto "NO" al cliente
                    numeroIntentos++;
                    if(numeroIntentos == 3){
                        salir = true;
                        desconectar = true;
                        cout << "\nMaximo de intentos permitidos. Desconectando cliente...";
                    }
                }

            } while(!salir);

            //CLIENTE CONECTADO!!!
            //ACA HAGAN LA LOGICA DE SUS PROGRAMAS QUE TIENEN QUE HACER USTEDES!

            //FALTA!! ACA SOFIA TENES QUE SETEAR LA VARIABLE desconectar a TRUE cuando el cliente aprete "cerrar sesion"
            //TENES QUE HACER LA LOGICA.
            printf("\n\nNo apretes ninguna tecla porque se resetea a esperar a un nuevo cliente (sofia te toca esta parte que es la de cerrar sesion).");
            system("pause>nul");
        } //ACA TERMINA EL BUCLE DE UN CLIENTE EN CONCRETO
    }//ACA TERMINA EL BUCLE INFINITO PARA BUSCAR INFINITOS CLIENTES
}

bool Login(char* usuario, char* password)
{
    //VARIABLE QUE SE VA A DEVOLVER TRUE SI EL USUARIO Y PASSWORD ESTAN OK, Y FALSE SI NO LO ESTA
    bool respuesta = false;
    //VARIABLE DEL ARCHIVO Y OPEN DEL MISMO
    ifstream credenciales;
    credenciales.open("credenciales.txt",ios::in);

    //CHECK SI NO EXISTE ARCHIVO ARROJA ERROR
    if(credenciales.fail())
    {
        cerr << "\n\nError al abrir el archivo" << endl;
        exit(1);
    }
    //VARIABLES QUE SE VAN A UTILIZAR PARA RECORRER EL ARCHIVO
    string storedUser;
    string storedPass;
    //PASAJE DE PARAMETROS, RECORRE ARCHIVO Y CHECKEA
    while(credenciales >> storedUser >> storedPass)
    {
        //SI EL USUARIO Y EL PASSWORD SON LOS MISMOS RESPUESTA = TRUE
        if(storedUser == string(usuario) && storedPass == string(password))
        {
        respuesta = true;
        }
    }
    return respuesta;
}
