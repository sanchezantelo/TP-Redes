#include <stdio.h>
#include <winsock2.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#define PORT 54321
#define IP "127.0.0.1"
#pragma comment (lib, "Ws2_32.lib" )

using namespace std;

bool Login(char* usuario, char* password);

int main(int arg, char** argv){
//---------------------------------------------------------------------------------------------------
//INICIALIZAR WINSOCK
WSAData wsaData; //Declaro una variable tipo data para inicializar winsock
WSAStartup(MAKEWORD(2,2), &wsaData); //Inicializo Winsock ver 2.2 WS2_32.dll
//----------------------------------------------------------------------------------------------------
//INICIALIZAR UN SOCKET
SOCKET sockServer = socket(AF_INET,SOCK_STREAM,0);
//-----------------------------------------------------------------------------------------------------
//CREAR ESTRUCTURA Y UNIR LOS DATOS DEL SOCKET CON BIND
struct sockaddr_in sin;
sin.sin_family = AF_INET; //Le decimos que use ipv4.
sin.sin_addr.s_addr = inet_addr(IP); //Direccion ip de la cual escuchará el servidor.
sin.sin_port = htons(PORT); //Puerto del cual escuchara el servidor
memset(sin.sin_zero,0,sizeof(sin.sin_zero)); //RELLENO ( arreglo de 8 bytes que SIEMPRE debera ser llenado con ceros por cuestiones problematicas...)

bind(sockServer,(struct sockaddr*)&sin, sizeof(sin)); //Al socket sockServer le agregamos datos (ip y puerto)
//----------------------------------------------------------------------------------------------------------
//EMPEZAR A ESCUCHAR LISTEN
listen(sockServer,0);

//USAR A ACEPTAR UNA CONEXION CON ACCEPT
while(1){
    struct sockaddr_storage addrstorage; //storage es para guardar los datos del cliente que se va a conectar.
    int length = sizeof(addrstorage); //ya que no sabes el tamaño de la conexion del cliente (ipv4, ipv6 u otro), necesitamos hacer un sizeof.

    printf("Esperando a un cliente...");
    SOCKET sockClient = accept(sockServer,(struct sockaddr*)&addrstorage,&length); //"en el socket sockServer, acepto la conexion proveniente de un cliente X
    //y voy a guardar los datos del cliente en addrstorage. Luego les devuelvo un socket del cliente para que puedan comunicarse entre ustedes que llamamos sockClient"
    system("cls");
    printf("Cliente Encontrado!.");


    //RECIBIMOS USUARIO Y CONTRASEÑA:

    char user[50] = "";
    char pass[50] = "";
    char respuesta[3] = "OK";
    printf("\nEsperando Ingreso de usuario y contrase%ca...", 164);
    recv(sockClient,user,sizeof(user),0); //recibo el usuario que escribio el cliente y lo guardo en user.
    recv(sockClient,pass,sizeof(pass),0); //recibo la contraseña que escribio el cliente y lo guardo en pass.

    //COMPROBAMOS EL USUARIO Y CONTRASEÑA EN credenciales.txt:
    //FALTA HACER!!!!!!!!!!

    bool respuestaLogin = Login(user, pass);
    if(respuestaLogin)
    {
        //TO-DO LOG A TXT
        cout<<"\nLogin Correcto"<<endl;
        //CLIENTE ACEPTADO
        send(sockClient, respuesta, sizeof(respuesta), 0); //envio el texto "OK" al cliente
    }




    printf("\nCliente conectado!");
    printf("\nNo apretes ninguna tecla porque se resetea a esperar a un nuevo cliente.");
    system("pause>nul");;
}
}

/*
* FUNCION LOGIN
* param
* char usuario
* char password
*/
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
