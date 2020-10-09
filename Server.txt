/*SERVIDOR INCLUYE:				CLIENTE INCLUYE:
	-SOCKET						-SOCKET
	-BIND						-CONNECT
	-LISTEN						-SEND
	-ACCEPT						-RECV
	-RECV-RECVFROM				-CLOSE
	-SEND-SENDTO
	-CLOSESOCKET
	*/
#include<stdio.h>
#include<winsock2.h>
#include <fcntl.h>
//#include<validar.h>
#define PORT 50122
#define IP "192.168.0.101"
#pragma comment (lib, "Ws2_32.lib" )
char mi_nombre[]="Yui hirasawa";
int z=0;
int main(int arg, char** argv){
//---------------------------------------------------------------------------------------------------
//INICIALIZAR WINSOCK
if (arg!=3){
	WSAData x; //Declaro una variable tipo data par ainicializar winsock
	 z=WSAStartup(MAKEWORD(1,1), &x); //Inicializo Winsock
	if(z!=0){//devuelve un numero distinto de cero en caso de error, y devuelve 0 si sale todo bien.
		printf("\n No se pudo iniciar la libreria Winsock.");
			getchar();
		exit(1);
		return 0;
	}
}
//----------------------------------------------------------------------------------------------------
//INICIALIZAR UN SOCKET
SOCKET p;
p=socket(AF_INET,SOCK_STREAM,0);
if(p==INVALID_SOCKET){ //INVALID SOCKET ES PARA socket() tambien -1
	printf("\nNo ha podido inicializar el Socket error %d", WSAGetLastError());
		getchar();
	exit(1);
}
//-----------------------------------------------------------------------------------------------------
//UNIR LOS DATOS CON BIND
struct sockaddr_in magnus;
/*1*/magnus.sin_family=AF_INET; //USARA TCP/IP ipv4 (short int)
/*2*/magnus.sin_addr.s_addr=inet_addr(IP);  //DIRECCION EN LA CUAL ESCUCHARA EL SERVIDOR en orden de bits de red(STRUCT IN_ADDR SIN_ADDR)
/*3*/magnus.sin_port=htons(PORT); //PUERTO EN EL CUAL ESCUCHARA EL SERVIDOR en orden de bits de red ( entero corto sin signo)
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
//-------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------
//RECIBIR CON RECV
//z=read(p2, recibir, 500);
/*printf("\n\nEsperando Mensaje Del Cliente...");
z=recv(p2,recibir,sizeof(recibir),0);
								if(z==SOCKET_ERROR){ //z valdra el nº de bytes recibidos en caso de que no sea error
									printf("\nNo se ha podido inicializar recv error %d",WSAGetLastError());
									getchar();
									exit(1);
									}
fflush(stdin); //quitar esto desp
printf("\n%s:%s",usuario,recibir);
*/

//MSG_PEEK: Acumula a los datos entrantes. Los datos se copian en el buffer pero no son removidos de la cola de la entrada.
//MSG_OOB: Proceso fuera de banda.
//ENVIAR CON SEND
char enviar[1000],recibir[1000];
while(1){
printf("\n%s:",mi_nombre);fgets(enviar,1000,stdin);
quitarn(enviar,1000);
z=send(p2,enviar,sizeof(enviar),0);
if(z==SOCKET_ERROR){
	printf("\nNo se ha podido inicializar send error %d",WSAGetLastError());
		getchar();
	exit(1);
}
if(recv(p2,recibir,sizeof(recibir),0)==SOCKET_ERROR)printf("No se ha podido inicializar recv error %d", WSAGetLastError());
printf("%s:%s",usuario,recibir);

}

getchar();

//------------------------------------------------------------------------------------------------------------
//CERRAR SOCKETS
shutdown(p2,SD_BOTH);
printf("\nConexion Terminada.");
getchar();
}

//-------------------------------------------------------------------------------------------------------------
//LIBERA LA DLL DE WINSOCK
shutdown(p,SD_BOTH);
//SD_RECEIVE: 0-Se bloquearán los mensajes entrantes subsiguientes
//SD_SEND: 1-Se bloquearán los subsiguientes mensajes enviados
//SD_BOTH: Deshabilita tanto el envío como la recepción de mensajes subsiguientes
z=WSACleanup();
//MSG_DONTROUTE: Especifica que los datos no deben estar sujetos a una ruta. Un Servidor de Sockets de Windows puede ignorar esta bandera.
//MSG_OOB: Envía los datos fuera de banda (solo para sockets del tipo SOCK_STREAM).
if(z==SOCKET_ERROR){//0 si se ejecuta correctamente
printf("\nNo se ha podido liberar la DLL error %d", WSAGetLastError());
getchar();
exit(1);
}
getchar();
//-----------------------------------------------------------------------------------
}
