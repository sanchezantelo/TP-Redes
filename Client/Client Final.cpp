#include<stdio.h>
#include <iostream>
#include<winsock2.h>
#include <Servicio.h>
using namespace std;
char nombreUsuario[1000];
SOCKET crearSocket();
sockaddr_in crear_sockaddr_in(char IP[16], int PORT);
int conexion(SOCKET sockClient, sockaddr_in sin);
int login(SOCKET sockclient);
void enviar(SOCKET sock, char *mensaje);
void altaServicio();
void gestionarPasajes();
void crearServicio(Servicio servicio);

int main(int arg, char** argv){
    int opcion = 0, error = 0;
    char IP[] = "127.0.0.1";
    const int PORT = 54321;
    SOCKET sockClient = 0;
    sockaddr_in sin;
    do {
        system("cls");
        cout << "1-Login\n2-Salir\n" << endl;
        cin >> opcion;
        switch(opcion){
            case 1:
                sockClient = crearSocket();
                sin = crear_sockaddr_in(IP, PORT);
                error = conexion(sockClient, sin);
                if(error == 0)
                    error = login(sockClient);
                break;
            case 2:
                exit(-1);
            default: break;
        }
    }while(error == -1);
    //-----------------------------------------------------------------------------------------------------

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
                altaServicio();
                system("pause>nul"); // Pausa
                break;

            case 2:
                // Lista de instrucciones de la opción 2
                gestionarPasajes();
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

int login(SOCKET sockClient){
    char contrasenia[1000] = {}, respuesta[2];
    int numeroIntentos = 0, error = 0;

    do {
        system("cls");
        //PEDIMOS EL NOMBRE DE USUARIO Y LO ENVIAMOS AL SERVIDOR.
        cout << "Nombre de Usuario: ";
        memset(nombreUsuario,0,1000);
        cin >> nombreUsuario;
        //PEDIMOS LA CONTRASEÑA Y SE LO ENVIAMOS AL SERVIDOR
        cout << "Contrase\xA4"<<"a: "; // \xA4 es la letra 'ñ'
        memset(contrasenia,0,1000);
        cin >> contrasenia;

        enviar(sockClient, nombreUsuario); //envio mi nombre de usuario al Servidor
        enviar(sockClient, contrasenia); //envio mi Contraseña al Servidor

        //ME QUEDO ESPERANDO PARA VER SI INGRESE BIEN EL USUARIO Y CONTRASEÑA.
        recv(sockClient, respuesta, sizeof(respuesta),0);

        if( strcmp( respuesta , "OK" ) != 0 ){
            cout << "\n\nNombre de usuario o Contrase\xA4" << "a incorrectos." << endl;
            system("pause>nul");
            system("cls");
            numeroIntentos++;
            if(numeroIntentos == 3) {
                error = -1;
                closesocket(sockClient);
            }
        }

    } while(error == 0 && strcmp( respuesta , "OK" ) != 0);

    return error; //retorna -1 si se supero el limite de intentos
}

void enviar(SOCKET sock, char *mensaje){
    int error = 0;
    error = send(sock, mensaje, sizeof(mensaje), 0); //envio mi nombre de usuario al Servidor
    if(error == SOCKET_ERROR){
        cout << "No se pudo enviar el mensaje. Error "<< WSAGetLastError();
        system("pause>nul");
        closesocket(sock);
        exit(-1);
    }
    return;
}

void altaServicio() {
    int seguir = 1;
    char opcion;
    int origen;
    string fecha;
    int turno;
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};

    Servicio serv= Servicio(1,"",1);

    while (seguir) {
        do {
            system("cls");
            cout << "Ingresar origen (1. Buenos Aires, 2. Mar del Plata)" << endl;
            cin >> origen;
            serv.setOrigen(origen);
        } while (origen != 1 && origen != 2);

        system("cls");
        cout << "Ingresar fecha (aaaa-mm-dd)" << endl;
        cin >> fecha;
        serv.setFecha(fecha);

        do {
            system("cls");
            cout << "Ingresar turno (1. manana, 2. tarde, 3. noche)" << endl;
            cin >> turno;
            serv.setTurno(turno);
        } while (turno < 1 || turno > 3);

        system("cls");
        cout << "Elegiste origen: " << origen_string[origen - 1] << ", fecha: " << fecha << ", turno: " << turno_string[turno - 1] << endl << "Los datos son correctos?" << endl;
        cout << "1. Si" << endl << "2. No, ingresarlos nuevamente" << endl;
        cin >> opcion;
        switch (opcion) {
            case '1':
                seguir = 0;
                crearServicio(serv);
            default: seguir = 0; break;
        }
        system("cls");
    }
}
void crearServicio(Servicio servicio){
    SOCKET sockClient = crearSocket();
    servicio.mostrar();
    enviar(sockClient,servicio.mensaje());
    system("PAUSE");
}


void gestionarPasajes() {
    int seguir = 1;
    char opcion;
    int origen;
    string fecha;
    int turno;
    char origen_string[3][20] = {"Vacio", "Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Vacio", "Manana", "Tarde", "Noche"};
    Servicio serv= Servicio(1,"",1);

    while (seguir) {
        do {
            system("cls");
            cout << "Buscar por origen (1. Buenos Aires, 2. Mar del Plata). [Si no desea buscar por origen ingrese 0]" << endl;
           cin >> origen;
           serv.setOrigen(origen);
        } while (origen < 0 || origen > 2);

        system("cls");
        cout << "Buscar por fecha (aaaa-mm-dd). [Si no desea buscar por fecha ingrese 0]" << endl;
        cin >> fecha;
        serv.setFecha(fecha);

        do {
            system("cls");
            cout << "Buscar por turno (1. manana, 2. tarde, 3. noche). [Si no desea buscar por turno ingrese 0]" << endl;
            cin >> turno;
            serv.setTurno(turno);
        } while (turno < 0 || turno > 3);

        system("cls");
        cout << "Elegiste origen: " << origen_string[origen] << ", fecha: " << fecha << ", turno: " << turno_string[turno] << endl << "Los datos son correctos?" << endl;
        cout << "1. Si" << endl << "2. No, ingresarlos nuevamente" << endl;
        cin >> opcion;
        switch (opcion) {
            case '1': seguir = 0;/*crearServicio(origen, fecha, turno);*/ break;
            case '2': break;
            case '\n': break;
            default: seguir = 0; break;
        }
        system("cls");
    }
}
