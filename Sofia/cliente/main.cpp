#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
#include <Servicio.h>
#include <cstring>
using namespace std;

void altaServicio(Cliente &cliente, Servicio &servicio);
void gestionarPasajes(Cliente &cliente, Servicio &servicio);
void verRegistrosDeActividades(Cliente &cliente);
void mostrarActividades(string actividades);
void cerrarSesion(Cliente &cliente);
void login(Cliente &cliente);
void menuEncabezado(void);
string service (char opcion, string recibido);
string menuReserva(string respuesta);

int main(){


     Cliente *Client = new Cliente();
     Servicio *Serv = new Servicio(0,"",0);
     login(*Client);
     int opcion=0;


    while(opcion!=4 || Client->getSesion()) {

        menuEncabezado();
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
                verRegistrosDeActividades(*Client);
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opción 4
                cerrarSesion(*Client);
                Client->setSesion(false);
                system("pause>nul"); // Pausa
                break;
        }
    };            // opción de SALIDA
    return 0;
}

void menuEncabezado(void){

  system("cls");        // Para limpiar la pantalla

        // Texto del menú que se verá cada vez despues de loguearse

        cout << "\n*********************************"<< endl;
        cout << "      RESERVA DE PASAJES         "  << endl;
        cout << "*********************************"  << endl;
        cout << "\n1. Alta servicio" << endl;
        cout << "\n2. Gestionar pasajes" << endl;
        cout << "\n3. Ver registro de actividades" << endl;
        cout << "\n4. Cerrar sesion" << endl;

        cout << "\nIngrese una opcion: ";

}


void login(Cliente &cliente){
    cliente.Recibir();
    string usuario;
    string contrasenia;
    string mensaje;
    int contador=0;

do{
    cout<<"\nIngrese Usuario:";
    cin>>usuario;
    cout<<"\nIngrese contrase\xA4"<<"a: "; // \xA4 es la letra 'ñ'
    cin>>contrasenia;
    mensaje="login;"+usuario+";"+contrasenia;
    cliente.Enviar(mensaje);

//cout<<cliente.Recibir()<<endl;

    if(cliente.Recibir().compare("autenticado")==0){
         cliente.setSesion(true);
         cliente.setuserName(usuario);
         cout<<"\nBienvenido al sistema!"<<endl;
    }
    else if(cliente.Recibir().compare("no autenticado")==0){
        Cliente *nuevocliente= new Cliente();
        cliente=*nuevocliente;
    }

     if(!cliente.getSesion()){
        cout<<"\nUsuario y contrase\xA4"<<"a incorrectos o supera maximo permitido de caracteres"<<endl;
        contador++;
     }

     if(contador==3){
      cout<<"\nSe supero la cantidad maxima de intentos de ingreso"<<endl;
      cliente.Enviar("salir;");
      cliente.CerrarSocket();
      system("PAUSE");
      exit(0);
      }

}while(!cliente.getSesion() && contador<3);
 system("PAUSE");
};



void altaServicio(Cliente &cliente, Servicio &servicio){
    int seguir = 1;
    char opcion;
    int origen;
    string fecha;
    int turno;
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};


    while (seguir && cliente.getSesion()) {
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
            case '1': {
                seguir = 0;
                cliente.Enviar(string("G1;" + servicio.mensaje()));
                string recibido = cliente.Recibir();
                if (recibido == "1")
                    cout << "El servicio se guardo correctamente" << endl;
                else if (recibido == "2")
                    cout << "El servicio ya existe" << endl;
                else if (recibido == "3")
                    cout << "No se pudo crear el servicio" << endl;
                system("pause");
                break;
            }
            case '2': break;
            default: seguir = 0; break;
        }
        system("cls");
    }
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
            case '1': {
                seguir = 0;
                cliente.Enviar(string("G2;" + servicio.mensaje()));
                string recibido = cliente.Recibir();
                cout << "Resultados segun busqueda: " << origen_string[origen] << ", Fecha: " << fecha << ", Turno: " << turno_string[turno] << endl;
                cout << recibido << endl;
                cout << "Ingrese el numero de servicio que desea elegir: 0 para salir" << endl;
                cin >> opcion;
                string respuesta = "";
                if (opcion=='0'){
                        break;}else{
                        respuesta = service (opcion, recibido);
                        cout << respuesta << endl;
                };
                cout << "El servicio elegido es: " << respuesta << ", desea continuar? 1.Si 2.No" << endl;
                cin >> opcion;
                switch (opcion){
                    case '1': {
                        seguir = 0;
                        menuReserva(respuesta);
                        //cliente.Enviar(string("G3;" + servicio.mensaje()));
                    }
                    case '2': break;
                    default: seguir = 0; break;
                }
                system("pause");
                break;
            }
            case '2': break;
            case '\n': break;
            default: seguir = 0; break;
        }
        system("cls");
    }
};

void verRegistrosDeActividades(Cliente &cliente){
  cliente.Enviar("MostrarActividad;"+cliente.getuserName());
  string recibido = cliente.Recibir();
   mostrarActividades(recibido);
  system("PAUSE");
}

void cerrarSesion(Cliente &cliente){
cliente.Enviar("salir;");
cliente.CerrarSocket();
};

void mostrarActividades(string actividades){
   char * cstr = new char [actividades.size()+1];
   strcpy (cstr, actividades.c_str());

  char * p = strtok (cstr,";");
  while (p!=0)
  {
    cout << p << '\n';
    p = strtok(NULL,";");
  }
}

string service (char opcion, string recibido){

    string prueba = "prueba";
    char * cstr = new char [recibido.size()+1];
    strcpy (cstr, recibido.c_str());

    char * aux = strtok (cstr, ")");
    while (aux != 0){
            //cout << aux << '\n';
            //char * pOpcion = &opcion;
            if (strcmp(aux, &opcion)<0){
                aux = strtok(NULL, "|");
                //cout << "entro" << endl;
                prueba=aux;
            }else{
                aux = strtok(NULL, "|");
            }//Aunque no sea igual, debo "cortarlo" para que siga el mismo formato. Solo se guarda cuando n) es igual a opcion.
            //cout << aux << '\n';
            aux = strtok(NULL, ")");
            if (strcmp(aux, &opcion)>0 && !prueba.empty()){
                break;
            }
    }
    return prueba;
}

string menuReserva(string respuesta){
    char * cstr = new char [respuesta.size()+1];
    strcpy (cstr, respuesta.c_str());

    char * aux = strtok (cstr, ";");
    string origen="";
    string fecha="";
    string turno="";
    while (aux != 0){
        origen = aux;
        fecha = strtok(NULL, ";");
        turno = strtok(NULL, "");
        break;
    };
    int _orig = stoi(origen);
    int _turn = stoi(turno);
    Servicio *servicio = new Servicio(_orig, fecha, _turn);
    servicio->mostrar();
    system("pause");
    return respuesta;
}
