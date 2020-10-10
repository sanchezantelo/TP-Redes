#include<stdio.h>
#include<winsock2.h>
char IP[100] = "127.0.0.1";
const int PORT = 54321, error = 0;

int main(int arg, char** argv){

WSAData wsaData; //Declaro una variable tipo data para inicializar winsock
WSAStartup(MAKEWORD(2,2), &wsaData); //Inicializo Winsock ver 2.2 WS2_32.dll
//----------------------------------------------------
SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);

//printf("\nDireccion del Servidor:");
//fgets(IP,100,stdin);
//quitarn(IP,100);

struct hostent *hp;
hp=(struct hostent*)gethostbyname(IP);
if(!hp){
	printf("\nNo se ha encontrado el Servidor error %d", WSAGetLastError());
	getchar();
	exit(1);
}

//---------------------------------------------------
struct sockaddr_in sin;
memcpy(&sin.sin_addr,hp->h_addr,hp->h_length);
sin.sin_family = hp->h_addrtype;
sin.sin_port = htons(PORT);
memset(sin.sin_zero,0,8);
connect(sockClient,(struct sockaddr*)&sin,sizeof(sin));
printf("\nConexion Establecida con:%s:%d\n", inet_ntoa(sin.sin_addr),PORT);

//RECIBO ALGO DEL SERVIDOR USUARIO: Y LE CONTESTO
//---------------------------------------------------
//char buffer[1000];
//recv(sockClient,buffer,sizeof(buffer),0);//Recibo "Usuario:"
//printf("\n%s", buffer);

char user[50], pass[50], buffer[1000], enviar[1000],nombre_servidor[100];
printf("User: ");
fflush(stdin);
fgets(user,50,stdin); //Le contesto a "Usuario:"
send(sockClient,user,sizeof(user),0); //envio mi Usuario al Servidor

printf("Password: ");
fflush(stdin);
fgets(pass,50,stdin); //Le contesto a "Usuario:"
send(sockClient,pass,sizeof(pass),0); //envio mi Usuario al Servidor

//-----------------------------------------------------------------------------------------------------
//RECIBO LA BIENVENIDA DEL SERVIDOR
system("cls");
recv(sockClient,buffer,sizeof(buffer),0);
printf("%s",buffer); //Recibo la bienvenida del servidor y la imprimo

printf("\n\n");
//---------------------------------------------------------------------------------
//EMPIEZA EL CHAT CON EL SERVIDOR
while(1){
recv(sockClient,buffer,sizeof(buffer),0);
printf("%s:%s",nombre_servidor,buffer);

fflush(stdin);
printf("\n%s:",user);
fgets(enviar,1000,stdin); //nombre del cliente
send(sockClient,enviar,sizeof(enviar),0);
}
//------------------------------------------------------------
shutdown(sockClient,SD_BOTH);
}
