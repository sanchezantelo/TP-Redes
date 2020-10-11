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
#include<validar.h>
char IP[100];
const int PORT=50122;
int main(int arg, char** argv){
WSAData x;
int z=WSAStartup(MAKEWORD(1,1),&x);
if(z!=0){
	printf("\nNo se ha podido inicializar Winsock.");
}
//----------------------------------------------------
SOCKET p=socket(AF_INET,SOCK_STREAM,0);
if(p==INVALID_SOCKET){
	printf("\nNo se ha podido inicializar el Socket error %d", WSAGetLastError());
}
//---------------------------------------------------
printf("\nDireccion del Servidor:");
fgets(IP,100,stdin);
quitarn(IP,100);

struct hostent *hp;
hp=(struct hostent*)gethostbyname(IP);
if(!hp){
	printf("\nNo se ha encontrado el Servidor error %d", WSAGetLastError());
	getchar();
	exit(1);
}

//---------------------------------------------------
struct sockaddr_in magnus;
memcpy(&magnus.sin_addr,hp->h_addr,hp->h_length);
magnus.sin_family=hp->h_addrtype;
magnus.sin_port=htons(PORT);
memset(magnus.sin_zero,0,8);
z=connect(p,(struct sockaddr*)&magnus,sizeof(magnus));
if(z==SOCKET_ERROR){
	printf("\nNo se ha podido inicializar Connect error %d", WSAGetLastError());
	closesocket(p);
	WSACleanup();getchar();return WSAGetLastError();
}

printf("\nConexion Establecida con:%s:%d\n", inet_ntoa(magnus.sin_addr),PORT);
//char str[20];
//printf("\nSi,Conexion Establecida con:%s\n", inet_ntop(hp->h_addrtype,magnus.sin_addr,str,INET_ADDRSTRLEN));
//La estructura hostent es utilizada para obtener informacion de un host remoto (regularmente se utiliza mas en la parte cliente.)
/*struct hostent {
   char *h_name;                   // El nombre oficial del nodo.
   char **h_aliases;                // Lista de Alias.
   int h_addrtype;                   // Tipo de dirección del nodo.
   int h_length;                       // Longitud de la dirección.
   char **h_addr_list;             // Lista de direcciones del nombre del servidor.

   #define h_addr  h_addr_list[0]  // Dirección, para la compatibilidad con
                                                  // anteriores.
};
*/
//------------------------------------------------------------
//RECIBO ALGO DEL SERVIDOR USUARIO: Y LE CONTESTO
char buffer[1000];
recv(p,buffer,sizeof(buffer),0);//Recibo "Usuario:"
printf("\n%s", buffer);

char usuario[50], enviar[1000],nombre_servidor[100];

fflush(stdin);
fgets(usuario,50,stdin); //Le contesto a "Usuario:"
quitarn(usuario,50);
send(p,usuario,sizeof(usuario),0); //envio mi Usuario al Servidor
recv(p,nombre_servidor,sizeof(nombre_servidor),0); //recibo el nombre del servidor(Yui Hirasawa)
//-----------------------------------------------------------------------------------------------------
//RECIBO LA BIENVENIDA DEL SERVIDOR
system("cls");
recv(p,buffer,sizeof(buffer),0);
printf("%s",buffer); //Recibo la bienvenida del servidor y la imprimo

printf("\n\n");
//---------------------------------------------------------------------------------
//EMPIEZA EL CHAT CON EL SERVIDOR
while(1){
recv(p,buffer,sizeof(buffer),0);
printf("%s:%s",nombre_servidor,buffer);

fflush(stdin);
printf("\n%s:",usuario);
fgets(enviar,1000,stdin); //nombre del cliente
quitarn(enviar,1000);//LE QUITO EL\N antes de enviarlo
send(p,enviar,sizeof(enviar),0);
}
//------------------------------------------------------------
shutdown(p,SD_BOTH);
}
