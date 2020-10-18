#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
using namespace std;

void altaServicio();
void gestionarPasajes(void);
void verRegistrosDeActividades(void);
void cerrarSesion(void);
void login(void);

Cliente *Client = new Cliente();

int main()
{


     int opcion;




    do {
        system("cls");        // Para limpiar la pantalla

        // Texto del men� que se ver� cada vez

        cout << "\n******RESERVA DE PASAJES*********\n\n" << endl;
        cout << "1. Alta servicio" << endl;
        cout << "2. Gestionar pasajes" << endl;
        cout << "3. Ver registro de actividades" << endl;
        cout << "4. Cerrar sesion" << endl;

        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Lista de instrucciones de la opci�n 1
                altaServicio();
                system("pause>nul"); // Pausa
                break;

            case 2:
                // Lista de instrucciones de la opci�n 2
                gestionarPasajes();
                system("pause>nul"); // Pausa
                break;

            case 3:
                // Lista de instrucciones de la opci�n 3
                verRegistrosDeActividades();
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opci�n 4
                cerrarSesion();
                system("pause>nul"); // Pausa
                break;
        }
    } while (opcion != 4);            // opci�n de SALIDA
    return 0;

}
void altaServicio(){

while (true){
    Client->Enviar();
    Client->Recibir();
}

};


void login(){
while (true){
    Client->Enviar();
    Client->Recibir();
}


};
void gestionarPasajes(void){};
void verRegistrosDeActividades(void){};
void cerrarSesion(void){};


