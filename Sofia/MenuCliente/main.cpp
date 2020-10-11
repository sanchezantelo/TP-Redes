#include <iostream>
#include "Pasaje.h"
using namespace std;

void altaServicio(void);
void gestionarPasajes(void);
void verRegistrosDeActividades(void);
void cerrarSesion(void);


int main()
{
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
                verRegistrosDeActividades();
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opción 4
                cerrarSesion();
                system("pause>nul"); // Pausa
                break;
        }
    } while (opcion != 4);            // opción de SALIDA
    return 0;

}
void altaServicio(void){
    std::string fecha("asd"),origen("asd"), turno("asd"), asiento("asd");
    Pasaje pje();
    cout<<"\n\nIngrese Origen:"<<endl;
 //   cout<<pasaje.asiento<<pasaje.origen<<pasaje.fecha<<pasaje.turno<<endl;
};
void gestionarPasajes(void){};
void verRegistrosDeActividades(void){};
void cerrarSesion(void){};
