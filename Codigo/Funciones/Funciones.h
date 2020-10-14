#include <stdio.h>
#include <iostream>
using namespace std;


//crearSocket() PERMITE CREAR Y VALIDAR LA CREACION DE UN SOCKET TANTO DEL PARTE DEL CLIENTE O DEL SERVIDOR.
//-----------------------------------------------------------------------------------------------------------------------
SOCKET crearSocket(){
    //INICIALIZAR WINSOCK Y VALIDAR
    int error = 0;
    WSAData wsaData; //Declaro una variable tipo data para inicializar winsock
    error = WSAStartup(MAKEWORD(2,2), &wsaData); //Inicializo Winsock ver 2.2 WS2_32.dll
    if(error != 0){
        cout << "No se pudo inicializar la libreria Winsock." << endl;
        system("pause>nul");
        exit(-1);
    }
    //INICIALIZAR UN SOCKET Y VALIDAR
    SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
    if(sockClient == INVALID_SOCKET){
        cout << "No se ha podido inicializar el Socket. Error " << WSAGetLastError() << endl;
        system("pause>nul");
        exit(-1);
    }
    return sockClient;
}


//crear_sockaddr_in() NOS PERMITE CREAR LA CONFIGURACION BASICA CON LOS DATOS DEL DESTINO (DEBE IR DEL LADO DEL CLIENTE)
//-----------------------------------------------------------------------------------------------------------------------
sockaddr_in crear_sockaddr_in(char IP[16], int PORT){
    struct hostent *remoteHost; //La estructura hostent es utilizada para obtener informacion de un host remoto (regularmente se utiliza mas en la parte cliente.)
    remoteHost = (struct hostent*)gethostbyname(IP);
    if(!remoteHost){
        cout << "No se ha encontrado el servidor. Error " << WSAGetLastError() << endl;
        system("pause>nul");
        exit(-1);
    }
    struct sockaddr_in sin; //Creamos una estructura para almacenar todos los datos del server.
    memcpy(&sin.sin_addr,remoteHost->h_addr,remoteHost->h_length); //asignamos la direccion ip
    sin.sin_family = remoteHost->h_addrtype; //asignamos que vamos a usar ipv4
    sin.sin_port = htons(PORT);  //asignamos puerto destino
    memset(sin.sin_zero,0,8); //rellenamos esta variable con ceros por cuestiones problematicas.
    return sin;
}


//conexion() NOS PERMITE ESTABLECER UNA CONEXION QUE VA DESDE EL CLIENTE HASTA EL SERVIDOR (DEBE IR DEL LADO DEL CLIENTE)
//-----------------------------------------------------------------------------------------------------------------------
int conexion(SOCKET sockClient, sockaddr_in sin){
    int error = 0;
    error = connect(sockClient,(struct sockaddr*)&sin, sizeof(sin)); //Se intenta conectar contra el servidor
    if(error == SOCKET_ERROR){
        system("cls");
        cout << "No se ha podido conectar al servidor. Connect error " << WSAGetLastError() << endl;
        closesocket(sockClient);
        WSACleanup();
        system("pause>nul");
    }
    return error;
}

//enviar() nos permite dado un socket, un mensaje y el tamaño del mensaje, enviar el mensaje al destino (ya sea al cliente o servidor).
//-----------------------------------------------------------------------------------------------------------------------
void enviar(SOCKET sock, char mensaje[], int tamanio){
    int error = 0;
    error = send(sock, mensaje, tamanio, 0); //envio un mensaje X
    if(error == SOCKET_ERROR){
        cout << "No se pudo enviar el mensaje. Error "<< WSAGetLastError();
        system("pause>nul");
        closesocket(sock);
        exit(-1); //salgo del programa
    }
    return;
}




