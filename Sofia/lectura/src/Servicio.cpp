#include "Servicio.h"
#include <string>
#include <fstream>
#include <dirent.h>
#include <cstring>

using namespace std;


Servicio::Servicio(){}

Servicio::~Servicio(){}

Servicio::Servicio(int _origen, char _fecha[21], int _turno)
{
    origen = _origen;
    strcpy(fecha, _fecha);
    turno = _turno;
    strcpy(filaA, "OOOOOOOOOOOOOOOOOOOO");
    strcpy(filaB, "OOOOOOOOOOOOOOOOOOOO");
    strcpy(filaC, "OOOOOOOOOOOOOOOOOOOO");
}

Servicio::Servicio(int _idServicio, int _origen, char _fecha[21], int _turno, char _filaA[21], char _filaB[21], char _filaC[21])
{
    idServicio = _idServicio;
    origen = _origen;
    strcpy(fecha, _fecha);
    turno = _turno;
    strcpy(filaA, _filaA);
    strcpy(filaB, _filaB);
    strcpy(filaC, _filaC);
}

void Servicio::setOrigen(int _origen)
{
    origen = _origen;
}

int Servicio::getOrigen()
{
    return origen;
}

void Servicio::setFecha(char _fecha[21])
{
    strcpy(fecha, _fecha);
}

char* Servicio::getFecha()
{
    return fecha;
}

void Servicio::setTurno(int _turno)
{
    turno = _turno;
}

int Servicio::getTurno()
{
    return turno;
}

void Servicio::setfilaA(char _filaA[21])
{
    strcpy(filaA, _filaA);
}

char* Servicio::getfilaA()
{
    return filaA;
}

void Servicio::setfilaB(char _filaB[21])
{
    strcpy(filaB, _filaB);
}

char* Servicio::getfilaB()
{
    return filaB;
}

void Servicio::setfilaC(char _filaC[21])
{
    strcpy(filaC, _filaC);
}

char* Servicio::getfilaC()
{
    return filaC;
}

void Servicio::mostrar()
{
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};

    cout << "###########################################" << endl;
    cout << "###############  Servicio  ################" << endl;
    cout << "## " << origen_string[getOrigen() - 1] << " ";
    cout << "## " << getFecha() << " ";
    cout << "## " << turno_string[getTurno() - 1] << " ## " << endl;
    cout << "###########################################" << endl;
    cout << "  | 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2" << endl;
    cout << "  | 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "A | ";
    for (int i = 0; i < 20; i++) {
        cout << getfilaA()[i] << " ";
    }
    cout << endl << "B | ";
    for (int i = 0; i < 20; i++) {
        cout << getfilaB()[i] << " ";
    }
    cout << endl << "  | =======================================" << endl;
    cout << "C | ";
    for (int i = 0; i < 20; i++) {
        cout << getfilaC()[i] << " ";
    }
    cout << endl <<"###########################################" << endl;
    cout << endl << endl;
}
char* Servicio::mensaje(){
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};
    string servicio;
    string delimitador=";";
    char mensaje[1000] = {};
    servicio+=origen_string[getOrigen() - 1];
    servicio+=delimitador;
    servicio+=getFecha();
    servicio+=delimitador;
    servicio+=turno_string[getTurno() - 1];
    strcpy(mensaje,servicio.c_str());
    cout<<mensaje<< endl;
    return mensaje;
}

string Servicio::crearServicio()
{
    string respuesta= "";
    respuesta = to_string(getOrigen()) + ";" + getFecha() + ";" + to_string(getTurno())+";";
    //FILA A
    for (int i = 0; i < 20; i++) {
    respuesta = respuesta + getfilaA()[i];
    }
    //FILA B
    respuesta = respuesta + ";";
    for (int i = 0; i < 20; i++) {
    respuesta = respuesta + getfilaB()[i];
    }
    //FILA C
    respuesta = respuesta + ";";
    for (int i = 0; i < 20; i++) {
    respuesta = respuesta + getfilaC()[i];
    }

    return respuesta;
}


int Servicio:: CrearServicio(char * message)
{
    /**si respuesta = 1 servicio creado con exito
    *               = 2 servicio ya existe
    *               = 3 error al crear servicio
    */
    int respuesta = 0;
    Servicio serv= Servicio(1,"",1);
    char origen[5] = "";
    char fecha[15] = "";
    char turno[5] = "";

    string servicioAGuardar;

    //se divide el mensaje en diferentes variables a traves del delimitador
    strcpy(origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(turno, strtok(NULL, ";"));


    //setea variables del servicio
    serv.setOrigen(atoi(origen));
    serv.setFecha(fecha);
    serv.setTurno(atoi(turno));

    string nombreArchivo = "servicios/" + string(serv.getFecha()) + ".data";
    fstream servicios;

    servicios.open(nombreArchivo, fstream::app | ios::binary);

    //Si no existe, arroja error
    if(!servicios)
    {
        cout<< "No se pudo abrir el archivo.";
        respuesta = 3;
    }
    //Siempre lo crea con el fstream pero por algun error se pone arriba, y aca sigue la logica
    else{
        cout<<"Se encontro archivo: "<<nombreArchivo<<endl;

        //to-do comparar si ya existe un servicio
        if(ServicioExiste(serv)) {
            cout << "El servicio ya existe" << endl;
            respuesta = 2;
        }
        else {
            servicios.write((char*)&serv, sizeof(Servicio));
            respuesta = 1;
        }

    }
    servicios.close();
    return respuesta;
}

//string Servicio:: reservarAsiento(char *message){
//    char c_origen[5] = "";
//    char fecha[15] = "";
//    char c_turno[5] = "";
//    char asiento[62][4] = {};
//
//    char filas[70] = "";
//    strcpy(c_origen, strtok(message , ";"));
//    strcpy(fecha, strtok(NULL, ";"));
//    strcpy(c_turno, strtok(NULL, ";"));
//
//    strcpy(filas, strtok(NULL, ";"));
//    strcpy(filas, strtok(NULL, ";"));
//    strcpy(filas, strtok(NULL, ";")); //filas de asiento.
//
//    char* aux = strtok(NULL, ";");
//    int i = 0;
//    int pos = 0;
//
//    while (aux != 0) {
//        if (i % 2 == 0) {
//            asiento[pos][0] = aux[0];
//            asiento[pos][1] = aux[1]; // aca seria todo menos aux[0]
//            asiento[pos][2] = aux[2];
//            cout << "PAR: " << asiento[pos][0] << " " << asiento[pos][1] << asiento[pos][2] << endl;
//        }
//        else {
//            asiento[pos][3] = aux[0];
//            cout << "IMPAR: " << asiento[pos][3] << endl;
//            pos++;
//        }
//        aux = strtok(NULL, ";|");
//        i++;
//    }
//
//    int origen = atoi(c_origen);
//    int turno = atoi(c_turno);
//    //char *msj = origen + ";" + fecha + ";" + turno;
//
//    Servicio* serv = new Servicio(origen, fecha, turno);
//
//    if ((ServicioExiste((Servicio(*serv)))==true))
//        {
//            list<Servicio> listaServicios;
//            list<Servicio> :: iterator it = listaServicios.begin();
//            listaServicios = buscarServicioPorFecha(fecha);
//            listaServicios = buscarServicioPorOrigen(listaServicios, origen);
//            listaServicios = buscarServicioPorTurno(listaServicios, turno);
//            i = 0;
//            while (asiento[i][0] != NULL) {
//                cout << "FILA: " << asiento[i][0] << " COLUMNA: " << asiento[i][1] << asiento[i][2] << " RESERVAR/LIBERA: " << asiento[i][3] << endl;
//                string filaA = serv->getfilaA();
//                string filaB = serv->getfilaB();
//                string filaC = serv->getfilaC();
//
//                if (asiento[i][0] == 'A') {
//                    filaA[asiento[i][1] - 1] = asiento[i][2];
//                } else if (asiento[i][0] == 'B') {
//                    filaB[asiento[i][1] - 1] = asiento[i][2];
//                } else if (asiento[i][0] == 'C') {
//                    filaC[asiento[i][1] - 1] = asiento[i][2];
//                }
//
//            setfilaA(filaA);
//            setfilaB(filaB);
//            setfilaC(filaC);
//            i++;
//            }
//        }
//        cout << "prueba" << endl;
//        system("pause");
//
//}

string Servicio:: buscarServicio(char * message) {
    int respuesta = 0;
    char c_origen[5] = "";
    char fecha[15] = "";
    char c_turno[5] = "";

    strcpy(c_origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(c_turno, strtok(NULL, ";"));

    int origen = atoi(c_origen);
    int turno = atoi(c_turno);

    string lst = "";
    list<Servicio> listaServicios;
    list<Servicio> :: iterator it = listaServicios.begin();

    if (string(fecha) != "0") {
        listaServicios = buscarServicioPorFecha(fecha);
    }
    else {
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR = opendir("servicios/") ) {
            while(entry = readdir(pDIR)) {
                if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
                    list<Servicio> lista;
                    list<Servicio> :: iterator it = lista.begin();
                    lista = buscarServicioPorFecha(string(entry->d_name).substr(0,10));
                    listaServicios.splice(listaServicios.end(), lista);
                }
            }
            closedir(pDIR);
        }
    }
    if (origen != 0) {
        listaServicios = buscarServicioPorOrigen(listaServicios, origen);
    }
    if (turno != 0) {
        listaServicios = buscarServicioPorTurno(listaServicios, turno);
    }

    int i=0;
    for (it = listaServicios.begin(); it != listaServicios.end(); ++it) {
        i++;
        lst = lst + to_string(i) + ")" + to_string(((Servicio)* it).getOrigen()) + ";" + ((Servicio)* it).getFecha() + ";" + to_string(((Servicio)* it).getTurno()) + "|";
    }
    cout << lst << endl;
    return lst;
}

string Servicio:: encontradoServicio(char * message) {
    int respuesta = 0;
    char c_origen[5] = "";
    char fecha[15] = "";
    char c_turno[5] = "";

    strcpy(c_origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(c_turno, strtok(NULL, ";"));

    int origen = atoi(c_origen);
    int turno = atoi(c_turno);

    string lst = "";
    list<Servicio> listaServicios;
    list<Servicio> :: iterator it = listaServicios.begin();

    if (string(fecha) != "0") {
        listaServicios = buscarServicioPorFecha(fecha);
    }
    else {
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR = opendir("servicios/") ) {
            while(entry = readdir(pDIR)) {
                if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
                    list<Servicio> lista;
                    list<Servicio> :: iterator it = lista.begin();
                    lista = buscarServicioPorFecha(string(entry->d_name).substr(0,10));
                    listaServicios.splice(listaServicios.end(), lista);
                }
            }
            closedir(pDIR);
        }
    }
    if (origen != 0) {
        listaServicios = buscarServicioPorOrigen(listaServicios, origen);
    }
    if (turno != 0) {
        listaServicios = buscarServicioPorTurno(listaServicios, turno);
    }

    int i=0;
    for (it = listaServicios.begin(); it != listaServicios.end(); ++it) {
        i++;
        lst = lst + to_string(i) + ")" + to_string(((Servicio)* it).getOrigen()) + ";" + ((Servicio)* it).getFecha() + ";" + to_string(((Servicio)* it).getTurno()) + ";"
        + ((Servicio)* it).getfilaA() + ";" + ((Servicio)* it).getfilaB() + ";" + ((Servicio)* it).getfilaC() + "|";
    }
    cout << lst << endl;
    return lst;
}

list<Servicio> Servicio:: buscarServicioPorFecha(string fecha) {
    list<Servicio> lista;
    list<Servicio> :: iterator it = lista.begin();

    string _origen, _fecha, _turno, _filaA, _filaB, _filaC;
    string nombreArchivo = "servicios/" + string(fecha) + ".data";
    ifstream servicios;

    servicios.open(nombreArchivo, fstream::in);

    if(!servicios)
    {
        cout<< "No se pudo abrir el archivo.";
    }
    //Siempre lo crea con el fstream pero por algun error se pone arriba, y aca sigue la logica
    else{
        cout<<"Se encontro archivo: "<<nombreArchivo<<endl;

        while (!servicios.eof()) {
            Servicio serv = Servicio(0, "0", 0);
            servicios.read((char*)&serv, sizeof(Servicio));
            if (serv.getOrigen() != 0) {
                serv.mostrar();
                lista.insert(it, serv);
            }
        }
    }
    servicios.close();
    return lista;
}

list<Servicio> Servicio:: buscarServicioPorOrigen(list<Servicio> lista, int origen) {
    list<Servicio> :: iterator it = lista.begin();

    for (it = lista.begin(); it != lista.end(); ++it) {
        if (((Servicio)* it).getOrigen() != origen) {
            it = lista.erase(it);
            --it;
        }

    }

    return lista;
}

list<Servicio> Servicio:: buscarServicioPorTurno(list<Servicio> lista, int turno) {
    list<Servicio> :: iterator it = lista.begin();

    for (it = lista.begin(); it != lista.end(); ++it) {
        if (((Servicio)* it).getTurno() != turno) {
            it = lista.erase(it);
            --it;
        }
    }

    return lista;
}

//to-do
bool Servicio:: ServicioExiste(Servicio servicio)
{
    bool existe = false;
    list<Servicio> lista;
    list<Servicio> :: iterator it = lista.begin();

    lista = buscarServicioPorFecha(servicio.getFecha());

    for (it = lista.begin(); it != lista.end(); ++it) {
        if (((Servicio)* it).getOrigen() == servicio.getOrigen() && ((Servicio)* it).getTurno() == servicio.getTurno()) {
            existe = true;
        }
    }

    return existe;
}

