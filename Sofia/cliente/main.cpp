#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
#include <Servicio.h>
#include <cstring>
#include <vector>
#include <iterator>
#include <sstream>


using namespace std;

void altaServicio(Cliente &cliente, Servicio &servicio);
void gestionarPasajes(Cliente &cliente, Servicio &servicio);
void verRegistrosDeActividades(Cliente &cliente);
void mostrarActividades(string actividades);
void cerrarSesion(Cliente &cliente);
void login(Cliente &cliente);
void menuEncabezado(void);
void toText (string recibido);
string service (char opcion, string recibido);
string menuReserva(Cliente &cliente, string respuesta);
string servicioSelected(string s, char opc);
string servicioTexto(string servicio);

int main(){
    bool status=false;
    int puerto=0;
    string ip="";
    Cliente *Client = new Cliente(ip,puerto);
    do{
     cout<<"Ingrese direccion ip del servidor: ";
     cin>>ip;
     Client->setIp(ip);
     system("cls");
     cout<<"Ingrese puerto: ";
     cin>>puerto;
     system("cls");
     Client->setPuerto(puerto);
     status=Client->conectar();
     }while(!status);

     Servicio *Serv = new Servicio(0,"",0);
     login(*Client);
     int opcion=0;

    while(opcion!=4 || Client->getSesion()) {

        if(!Client->timeOut()){
        menuEncabezado();

        cin >> opcion;
        }else{
        opcion=4;
        }
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
                system("cls");
                main();
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
        cliente.setSesion(false);
    }

     if(!cliente.getSesion()){
        cout<<"\nUsuario y contrase\xA4"<<"a incorrectos"<<endl;
        system("PAUSE");
        system("cls");
        contador++;
     }

     if(contador==3){
      cout<<"\nSe supero la cantidad maxima de intentos de ingreso"<<endl;
      cliente.Enviar("salir;");
      cliente.CerrarSocket();
      system("PAUSE");
      system("cls");
      main();
      }

}while(!cliente.getSesion() && contador<3);
 system("PAUSE");
};



void altaServicio(Cliente &cliente, Servicio &servicio){
    int seguir = 1;
    char opcion;
    int origen;
    char fecha[11];
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
    char fecha[11];
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
                if(recibido == "NS")
                {
                    cout << "No se encontro ningun resultado"<<endl;
                    system("pause");
                    break;
                }
                cout << "Resultados segun busqueda: " << origen_string[origen] << ", Fecha: " << fecha << ", Turno: " << turno_string[turno] << endl;
                toText(recibido);
                cout << "Ingrese el numero de servicio que desea elegir: 0 para salir" << endl;
                cin >> opcion;
                string respuesta = "";

                if (opcion=='0'){
                        break;}else{
                        respuesta = servicioSelected (recibido, opcion);
                        cout << respuesta << endl;
                };
                string servicioToString = servicioTexto(respuesta);
                cout << "El servicio elegido es: " << servicioToString << ", desea continuar? 1.Si 2.No \n" << endl;
                cin >> opcion;

                switch (opcion){
                    case '1': {
                        system("cls");
                        seguir = 0;
                        menuReserva(cliente, respuesta);
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
  system("cls");
  cliente.Enviar("MostrarActividad;"+cliente.getuserName());
  string recibido = cliente.Recibir();
  mostrarActividades(recibido);
  system("PAUSE");
}

void cerrarSesion(Cliente &cliente){
cliente.Enviar("salir;");
cliente.CerrarSocket();
system("PAUSE");
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

void toText (string recibido){
    char * cstr = new char [recibido.size()+1];
    strcpy (cstr, recibido.c_str());

    string mostrar = "";
    char * aux = strtok (cstr, ")");
    while (aux != 0){
        cout << aux << ")";
        aux = strtok(NULL, ";");
        if(stricmp("1", aux))
        {
            mostrar = mostrar + " Mar del Plata a Buenos Aires ";
        }else
            {
                mostrar = mostrar + " Buenos Aires a Mar del Plata ";
            }
        aux = strtok(NULL, ";");
        mostrar = mostrar + " el " + aux;
        aux = strtok(NULL, "|");
        int x = atoi(aux);
        switch (x){
            case 1: mostrar += " turno Manana";
            break;
            case 2: mostrar += " turno Tarde";
            break;
            case 3: mostrar += " turno Noche";
            break;
            default: mostrar += " Error";
        }
        cout << mostrar << '\n';
        mostrar = "";
        aux = strtok(NULL,")");
    }
}

string servicioTexto(string servicio)
{

    char origen[2] = "";
    char fecha[13] = "";
    char turno[2] = "";

    char * serviceChar = new char [servicio.size()+1];
    strcpy (serviceChar, servicio.c_str());

    string servicioARetornar;
    strcpy(origen, strtok(serviceChar , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(turno, strtok(NULL, ";"));
    string fechaString = string(fecha, 10);


    if(stricmp("1", origen) == 0)
    {
        servicioARetornar = " Buenos Aires a Mar del Plata ";
    }
    else if(stricmp("2", origen) == 0)
    {
        servicioARetornar = " Mar del Plata a Buenos Aires ";
    }

    servicioARetornar = servicioARetornar + fechaString;

    if(stricmp("1", turno) == 0)
    {
        servicioARetornar = servicioARetornar + " Manana";
    }
    else if(stricmp("2", turno) == 0)
    {
        servicioARetornar = servicioARetornar + " Tarde";
    }
    else if(stricmp("3",turno) == 0)
    {
        servicioARetornar = servicioARetornar + " Noche";
    }

    return servicioARetornar;
}

string servicioSelected(string recibido, char opcion)
{
    string prueba = "error";
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

string menuReserva(Cliente &cliente, string respuesta){
    char * cstr = new char [respuesta.size()+1];
    strcpy (cstr, respuesta.c_str());
    string asientos="";

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
    char asiento[2];
    int opc = 0;
    int a = 1;
    int _orig = stoi(origen);
    int _turn = stoi(turno);
    char _fech[11];
    strcpy(_fech, fecha.c_str());
    Servicio *servicio = new Servicio(_orig, _fech, _turn);
    cliente.Enviar(string("G3;" + respuesta));
    //string resp = cliente.Recibir();
    servicio->mostrar();
    int cantAsientos = 0;
    while (a==1)
    {
        cantAsientos++;
        cout << "Ingrese asiento a reservar o liberar: " << endl;
        cin >> asiento;
        cout << "1. Reservar. 2. Liberar" << endl;
        cin >> opc;
        switch (opc){
            case 1 : asientos = asientos + asiento + ";" + "x" + "|";
            break;
            case 2 : asientos = asientos + ";" + asiento + ";" + "o" + "|";
            break;
            default: break;
        }
        cout << "Desea reservar o liberar otro asiento? 1.Si 2.No" << endl;
        cin >> a;
    }

    char *asientosToChar = new char[asientos.length() + 1];
    strcpy(asientosToChar, asientos.c_str());
    string filasAsiento = servicio-> reservayliberaAsientos(asientosToChar, cantAsientos);
    cout <<filasAsiento <<endl;
    string resp = cliente.Recibir();
    toText(resp);


    cliente.Enviar(string("G4;" + resp));
    string p = cliente.Recibir();
    cout << p << endl;
    system("pause");
    return p;
}
