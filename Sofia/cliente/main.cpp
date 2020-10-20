#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
using namespace std;

void altaServicio();
void gestionarPasajes(void);
void verRegistrosDeActividades(void);
void cerrarSesion(Cliente &cliente);
void login(Cliente &cliente);


int main()
{

     Cliente *Client = new Cliente();
     login(*Client);

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
                cerrarSesion(*Client);
                system("pause>nul"); // Pausa
                break;
        }
    } while (opcion != 4);            // opci�n de SALIDA
    return 0;

}
void altaServicio(){
};


void login(Cliente &cliente){

string usuario;
string contrasenia;
string mensaje;

cliente.Enviar("login");
cout<<cliente.Recibir();

 // for(int i=0;i<=2;i++){
    cout<<"Ingrese Usuario:"<<endl;
    cin>>usuario;
    cout<<"Ingrese contrase\xA4"<<"a: "<<endl; // \xA4 es la letra '�'
    cin>>contrasenia;
    mensaje=""+usuario+";"+contrasenia;
    cliente.Enviar(mensaje);

    system("PAUSE");


//}
};
void gestionarPasajes(void){};
void verRegistrosDeActividades(void){};

void cerrarSesion(Cliente &cliente){
cliente.Enviar("salir");
};


