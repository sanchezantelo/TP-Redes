#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
#include <Servicio.h>
using namespace std;

void altaServicio(Cliente &cliente, Servicio &servicio);
void gestionarPasajes(Cliente &cliente, Servicio &servicio);
void verRegistrosDeActividades(void);
void cerrarSesion(Cliente &cliente);
void login(Cliente &cliente);


int main()
{

     Cliente *Client = new Cliente();
     login(*Client);
     Servicio *Serv = new Servicio(0,"",0);


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
                altaServicio(*Client, *Serv);
                system("pause>nul"); // Pausa
                break;

            case 2:
                // Lista de instrucciones de la opción 2
                gestionarPasajes(*Client, *Serv);
                system("pause>nul"); // Pausa
                break;

            case 3:
                // Lista de instrucciones de la opción 3
                verRegistrosDeActividades();
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opción 4
                cerrarSesion(*Client);
                system("pause>nul"); // Pausa
                break;
        }
    } while (opcion != 4);            // opción de SALIDA
    return 0;

}
void altaServicio(Cliente &cliente, Servicio &servicio){
    int seguir = 1;
    char opcion;
    int origen;
    string fecha;
    int turno;
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};


    while (seguir) {
        do {
            system("cls");
            cout << "Ingresar origen (1. Buenos Aires, 2. Mar del Plata)" << endl;
            cin >> origen;
            servicio.setOrigen(origen);
        } while (origen != 1 && origen != 2);

        system("cls");
        cout << "Ingresar fecha (aaaa-mm-dd)" << endl;
        cin >> fecha;
        servicio.setFecha(fecha);

        do {
            system("cls");
            cout << "Ingresar turno (1. manana, 2. tarde, 3. noche)" << endl;
            cin >> turno;
            servicio.setTurno(turno);
        } while (turno < 1 || turno > 3);

        system("cls");
        cout << "Elegiste origen: " << origen_string[origen - 1] << ", fecha: " << fecha << ", turno: " << turno_string[turno - 1] << endl << "Los datos son correctos?" << endl;
        cout << "1. Si" << endl << "2. No, ingresarlos nuevamente" << endl;
        cin >> opcion;
        switch (opcion) {
            case '1':
                seguir = 0;
                cliente.Enviar(string("G1;" + servicio.mensaje()));
            default: seguir = 0; break;
        }
        system("cls");
    }
};


void login(Cliente &cliente){
    cliente.Recibir();
    string usuario;
    string contrasenia;
    string mensaje;

    bool ingresa=false;
    int contador=0;

do{
    cout<<"Ingrese Usuario:"<<endl;
    cin>>usuario;
    cout<<"Ingrese contrase\xA4"<<"a: "<<endl; // \xA4 es la letra 'ñ'
    cin>>contrasenia;
    mensaje="login;"+usuario+";"+contrasenia;
    cliente.Enviar(mensaje);

//cout<<cliente.Recibir()<<endl;

    if(cliente.Recibir().compare("autenticado")==0){
         ingresa=true;
         contador=3;
         cout<<"correcto"<<endl;
    }
    if(cliente.Recibir().compare("no autenticado")==0){
        cout<<"no ingreso"<<endl;
        Cliente *nuevocliente= new Cliente();
        cliente=*nuevocliente;
        contador++;
     }

}while(ingresa==false && contador< 3);
system("PAUSE");
};
void gestionarPasajes(Cliente &cliente, Servicio &servicio){
    int seguir = 1;
    char opcion;
    int origen;
    string fecha;
    int turno;
    char origen_string[3][20] = {"Vacio", "Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Vacio", "Manana", "Tarde", "Noche"};

    while (seguir) {
        do {
            system("cls");
            cout << "Buscar por origen (1. Buenos Aires, 2. Mar del Plata). [Si no desea buscar por origen ingrese 0]" << endl;
           cin >> origen;
           servicio.setOrigen(origen);
        } while (origen < 0 || origen > 2);

        system("cls");
        cout << "Buscar por fecha (aaaa-mm-dd). [Si no desea buscar por fecha ingrese 0]" << endl;
        cin >> fecha;
        servicio.setFecha(fecha);

        do {
            system("cls");
            cout << "Buscar por turno (1. manana, 2. tarde, 3. noche). [Si no desea buscar por turno ingrese 0]" << endl;
            cin >> turno;
            servicio.setTurno(turno);
        } while (turno < 0 || turno > 3);

        system("cls");
        cout << "Elegiste origen: " << origen_string[origen] << ", fecha: " << fecha << ", turno: " << turno_string[turno] << endl << "Los datos son correctos?" << endl;
        cout << "1. Si" << endl << "2. No, ingresarlos nuevamente" << endl;
        cin >> opcion;
        switch (opcion) {
            case '1': seguir = 0;
            cliente.Enviar(string("G2;" + servicio.mensaje()));
            case '2': break;
            case '\n': break;
            default: seguir = 0; break;
        }
        system("cls");
    }
}

;
void verRegistrosDeActividades(void){};

void cerrarSesion(Cliente &cliente){
cliente.Enviar("salir;");
cliente.CerrarSocket();
};




