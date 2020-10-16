#include<stdio.h>
#include <iostream>
#include<winsock2.h>
#include <Servicio.h>
#include "../Funciones/Funciones.h"
using namespace std;
char user[1000] = "";
SOCKET crearSocket();
sockaddr_in crear_sockaddr_in(char IP[16], int PORT);
int conexion(SOCKET sockClient, sockaddr_in sin);
int login(SOCKET sockclient);
void enviar(SOCKET sock, char *mensaje, int tamanio);
void altaServicio(SOCKET sock);
void gestionarPasajes();
void crearServicio(SOCKET sock, Servicio servicio);

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
                if(error == 0) // Si error == 0 quiere decir que está todo bien.
                    error = login(sockClient); // Si no hubo problemas en el login error seguira valiendo 0
                break;
            case 2:
                exit(-1); //Sale del programa retornando -1.
            default: break;
        }
    }while(error == -1); //si hubo algun error, vuelve al menu principal.

    //-----------------------------------------------------------------------------------------------------

    do {
        system("cls");
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
                altaServicio(sockClient);
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




int login(SOCKET sockClient){
    char pass[1000] = "", respuesta[3] = "";
    int numeroIntentos = 0, error = 0;
    do {
        system("cls");
        //PEDIMOS EL NOMBRE DE USUARIO Y LO ENVIAMOS AL SERVIDOR.
        cout << "Nombre de Usuario: ";
        memset(user,0,1000);
        cin >> user;
        enviar(sockClient, user, sizeof(user)); //envio mi nombre de usuario al Servidor

        //PEDIMOS LA CONTRASEÑA Y SE LO ENVIAMOS AL SERVIDOR
        cout << "Contrase\xA4"<<"a: "; // \xA4 es la letra 'ñ'
        memset(pass,0,1000);
        cin >> pass;
        enviar(sockClient, pass, sizeof(pass)); //envio mi Contraseña al Servidor

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

void altaServicio(SOCKET sock) {
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
                crearServicio(sock, serv);
            default: seguir = 0; break;
        }
        system("cls");
    }
}
void crearServicio(SOCKET sock, Servicio servicio){
    servicio.mostrar();
    enviar(sock,servicio.mensaje(), sizeof(servicio.mensaje()));
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
