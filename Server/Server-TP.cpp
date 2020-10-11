#include <stdio.h>
#include <winsock2.h>
#define PORT 54321
#define IP "192.168.0.10"
#pragma comment (lib, "Ws2_32.lib" )
int main(int arg, char** argv){
int z = 0;
char mi_nombre[]="Yui hirasawa";
//---------------------------------------------------------------------------------------------------
//INICIALIZAR WINSOCK
    if (arg != 3){
        WSAData wsaData; //Declaro una variable tipo data para inicializar winsock
        z = WSAStartup(MAKEWORD(2,2), &wsaData); //Inicializo Winsock
        if(z != 0){//devuelve un numero distinto de cero en caso de error, y devuelve 0 si sale todo bien.
            printf("\n No se pudo iniciar la libreria Winsock.");
            getchar();
            exit(-1);
        }
    }
//----------------------------------------------------------------------------------------------------
//INICIALIZAR UN SOCKET
SOCKET p;
p = socket(AF_INET,SOCK_STREAM,0);
if(p == INVALID_SOCKET){ //INVALID SOCKET ES PARA socket() tambien -1
	printf("\nNo ha podido inicializar el Socket error %d", WSAGetLastError());
    getchar();
	exit(-1);
}
//-----------------------------------------------------------------------------------------------------
//CREAR ESTRUCTURA Y UNIR LOS DATOS CON BIND
struct sockaddr_in magnus; //creo una variable estructura llamada sin
magnus.sin_family = AF_INET; //USARA TCP/IP ipv4 (short int)
magnus.sin_addr.s_addr = inet_addr(IP);  //DIRECCION EN LA CUAL ESCUCHARA EL SERVIDOR en orden de bits de red(STRUCT IN_ADDR SIN_ADDR)
magnus.sin_port = htons(PORT); //PUERTO EN EL CUAL ESCUCHARA EL SERVIDOR en orden de bits de red ( entero corto sin signo)
memset(magnus.sin_zero,0,sizeof(magnus.sin_zero)); //RELLENO ( arreglo de 8 bytes que siempre debera ser llenado con ceros)(UNSIGNED CHAR)

z = bind(p,(struct sockaddr*)&magnus, sizeof(magnus));
if(z == SOCKET_ERROR){  //tambien -1
	printf("\nNo se ha podido enlazar Bind error %d", WSAGetLastError());
    getchar();
	exit(-1);
}

//----------------------------------------------------------------------------------------------------------
//EMPEZAR A ESCUCHAR LISTEN
z = listen(p,SOMAXCONN);//solo puede atender a 1 cliente a  la ves hasta un maximo de SOMAXCONN
if(z == SOCKET_ERROR){ //tambien -1
	printf("\nNo se ha podido inicializar Listen error %d",WSAGetLastError());
    getchar();
	exit(1);
}

//USAR A ACEPTAR UNA CONEXION CON ACCEPT
while(1){
struct sockaddr_storage mefisto; //storage es para usar en accept
int tamanio = sizeof(mefisto); //hay que hacerlo asi ya que sino no te deja
system("cls");
printf("\nEsperando a un cliente...");
SOCKET p2 = accept(p,(struct sockaddr*)&mefisto,&tamanio);
if(p2==INVALID_SOCKET){
	printf("\nNo se ha podido inicializar accept error %d",WSAGetLastError());
		getchar();
	exit(1);
}
system("cls");
printf("Cliente Encontrado.");
//----------------------------------------------------------------------------------------------------
char nombre_usuario[]="Usuario:",contrasena[]="Contrasena:", usuario[50];
z=send(p2,nombre_usuario,sizeof(nombre_usuario),0);
if(z==SOCKET_ERROR){
	printf("No se ha podido inicializar send error %d", WSAGetLastError());
}
if(recv(p2,usuario,sizeof(usuario),0)==SOCKET_ERROR)printf("No se ha podido inicializar recv error %d",WSAGetLastError()); //recibo su nombre de usuario
printf("Nombre del Cliente: \"%s\"\n",usuario); //imprimo su nombre de Usuario
char bienvenido[150]="Bienvenido Al Canal de Yui ";
send(p2,mi_nombre,sizeof(mi_nombre),0);//le envio mi nombre de usuario(Yui Hirasawa)
strcat(bienvenido,usuario);
send(p2,bienvenido,sizeof(bienvenido),0); //Le  envio la Bienvenida
}
}
