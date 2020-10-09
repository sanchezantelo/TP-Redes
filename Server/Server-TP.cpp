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
        WSAData x; //Declaro una variable tipo data para inicializar winsock
        z = WSAStartup(MAKEWORD(1,1), &x); //Inicializo Winsock
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
/*1*/magnus.sin_family = AF_INET; //USARA TCP/IP ipv4 (short int)
/*2*/magnus.sin_addr.s_addr = inet_addr(IP);  //DIRECCION EN LA CUAL ESCUCHARA EL SERVIDOR en orden de bits de red(STRUCT IN_ADDR SIN_ADDR)
/*3*/magnus.sin_port = htons(PORT); //PUERTO EN EL CUAL ESCUCHARA EL SERVIDOR en orden de bits de red ( entero corto sin signo)
/*4*/memset(magnus.sin_zero,0,sizeof(magnus.sin_zero)); //RELLENO ( arreglo de 8 bytes que siempre debera ser llenado con ceros)(UNSIGNED CHAR)
// La intension de este arreglo inutil (aparentemente) es hacer que la estructura sockaddr_in, siempre mida 16 bytes.
/*1*///2 BYTES (SHORT INT)
/*2*///2 BYTES (STRUCT IN_ADDR SIN_ADDR) (me parece que es unsigned long)
/*3*///4 BYTES (UNSIGNED SHORT INT)
/*4*///8 BYTES (UNSIGNED CHAR)
//RESULTADO=16BYTES
//Sockaddr_in==16BYTES
/*
//ESTA ESTRUCTURA SIRVE COMO UN CASTING YA QUE DEBERAN LIDIAR CON ESTRUCTURAS SOCKET PROVENIENTES
//DE DIFERENTES FAMILIAS DE PROTOCOLOS SOPORTADOS, ANTERIORMENTE SE UTILIZABA VOID* EN VES DE ESTA ESTRUCTURA, PERO SE LO CAMBIO.
struct sockaddr {
   unsigned short sa_family;  // familia de la dirección
   char sa_data[14];          // 14 bytes de la direcció del protocolo
};
*/
//sa_family==2BYTES
//sa_data==14BYTES
//RESULTADO=16BYTES
//Sockaddr   ==16BYTES
z=bind(p,(struct sockaddr*)&magnus,sizeof(magnus));
if(z==SOCKET_ERROR){  //tambien -1
	printf("\nNo se ha podido enlazar Bind error %d", WSAGetLastError());
		getchar();
	exit(1);
}

//----------------------------------------------------------------------------------------------------------
//EMPEZAR A ESCUCHAR LISTEN
z=listen(p,SOMAXCONN);//solo puede atender a 1 cliente a  la ves hasta un maximo de SOMAXCONN
if(z==SOCKET_ERROR){ //tambien -1
	printf("\nNo se ha podido inicializar Listen error %d",WSAGetLastError());
		getchar();
	exit(1);
}
//USAR A ACEPTAR UNA CONEXION CON ACCEPt
while(1){
struct sockaddr_storage mefisto; //storage es para usar en accept
int tamanio=sizeof(mefisto); //hay que hacerlo asi ya que sino no te deja
system("cls");
printf("\nEsperando a un cliente...");
SOCKET p2=accept(p,(struct sockaddr*)&mefisto,&tamanio);
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
