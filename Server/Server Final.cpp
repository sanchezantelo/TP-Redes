#include <stdio.h>
#include <winsock2.h>
#define PORT 54321
#define IP "127.0.0.1"
#pragma comment (lib, "Ws2_32.lib" )
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

    printf("\nEsperando a un cliente...");
    SOCKET sockClient = accept(sockServer,(struct sockaddr*)&addrstorage,&length); //"en el socket sockServer, acepto la conexion proveniente de un cliente X
    //y voy a guardar los datos del cliente en addrstorage. Luego les devuelvo un socket del cliente para que puedan comunicarse entre ustedes que llamamos sockClient"
    system("cls");
    printf("Cliente Encontrado!.");


    //RECIBIMOS USUARIO Y CONTRASEÑA:

    char user[50], pass[50];
    printf("\nEsperando Ingreso de usuario y contrase%ca...", 164);
    recv(sockClient,user,sizeof(user),0); //recibo el usuario que escribio el cliente y lo guardo en user.
    recv(sockClient,pass,sizeof(pass),0); //recibo la contraseña que escribio el cliente y lo guardo en pass.

    //COMPROBAMOS EL USUARIO Y CONTRASEÑA EN credenciales.txt:
    //FALTA HACER!!!!!!!!!!




    //CLIENTE ACEPTADO
    send(sockClient,"OK",2,0); //envio el texto "Usuario:" al cliente

    printf("\nCliente conectado!");
    printf("\nNo apretes ninguna tecla porque se resetea a esperar a un nuevo cliente.");
    system("pause>nul");;
}
}
