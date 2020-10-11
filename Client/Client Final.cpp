#include<stdio.h>
#include <iostream>
#include<winsock2.h>
using namespace std;

SOCKET crearSocket();
sockaddr_in crear_sockaddr_in(char IP[16], int PORT);
void conexion(SOCKET sockClient, sockaddr_in sin);

int main(int arg, char** argv){

char IP[] = "127.0.0.1", user[49], buffer[1000];
const int PORT = 54321;
SOCKET sockClient = crearSocket();
sockaddr_in sin = crear_sockaddr_in(IP, PORT);
conexion(sockClient, sin);

do {
    system("cls");
    printf("1-Login\n2-Salir\n\n");
    fflush(stdin);
    scanf("%c", buffer);
    switch(buffer[0]){
        case '1':
            system("cls");
            printf("Nombre de Usuario: ");
            fflush(stdin);
            fgets(user,1000,stdin);
            send(sockClient, user, sizeof(user), 0); //envio mi Usuario al Servidor

            printf("Contrase%ca: ", 164);
            fflush(stdin);
            memset(buffer,0,1000);
            fgets(buffer,1000,stdin);
            send(sockClient, buffer, sizeof(buffer), 0); //envio mi Contraseña al Servidor

            //me quedo esperando para ver si ingrese bien o mal el usuario y contraseña.
            memset(buffer,0,1000);
            recv(sockClient, buffer, sizeof(buffer),0);
            if(strcmp(buffer,"OK") != 0){
                system("cls");
                printf("Nombre de usuario o Contrase%ca incorrectos.", 164);
                getchar();
            }
            break;
        case '2': exit(1);
        default: break;
    }
}while(strcmp(buffer,"OK"));
//-----------------------------------------------------------------------------------------------------
int opcion;
    do {
        system("cls");        // Para limpiar la pantalla

        // Texto del menú que se verá cada vez

        cout << "\n******RESERVA DE PASAJES*********\n\n" << endl;
        cout << "1. Alta servicio" << endl;
        cout << "2. Gestionar pasajes" << endl;
        cout << "3. Ver registro de actividades" << endl;
        cout << "4. Cerrar sesion" << endl;

        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Lista de instrucciones de la opción 1
                //altaServicio();
                system("pause>nul"); // Pausa
                break;

            case 2:
                // Lista de instrucciones de la opción 2
                //gestionarPasajes();
                system("pause>nul"); // Pausa
                break;

            case 3:
                // Lista de instrucciones de la opción 3
                //verRegistrosDeActividades();
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opción 4
                //cerrarSesion();
                //shutdown(sockClient,SD_BOTH);
                system("pause>nul"); // Pausa
                break;
        }
    } while (opcion != 4);            // opción de SALIDA
}

SOCKET crearSocket(){
    WSAData wsaData; //Declaro una variable tipo data para inicializar winsock
    WSAStartup(MAKEWORD(2,2), &wsaData); //Inicializo Winsock ver 2.2 WS2_32.dll
    return socket(AF_INET,SOCK_STREAM,0);
}

sockaddr_in crear_sockaddr_in(char IP[16], int PORT){
    struct hostent *remoteHost;
    remoteHost = (struct hostent*)gethostbyname(IP);
    if(!remoteHost){
        printf("\nNo se ha encontrado el Servidor error %d", WSAGetLastError());
        getchar();
        exit(-1);
    }
    struct sockaddr_in sin; //Creamos una estructura para almacenar todos los datos del server.
    memcpy(&sin.sin_addr,remoteHost->h_addr,remoteHost->h_length); //asignamos la direccion ip
    sin.sin_family = remoteHost->h_addrtype; //asignamos que vamos a usar ipv4
    sin.sin_port = htons(PORT);  //asignamos puerto destino
    memset(sin.sin_zero,0,8); //rellenamos esta variable con ceros por cuestiones problematicas.
    return sin;
}

void conexion(SOCKET sockClient, sockaddr_in sin){
    connect(sockClient,(struct sockaddr*)&sin, sizeof(sin));
    return;
}
