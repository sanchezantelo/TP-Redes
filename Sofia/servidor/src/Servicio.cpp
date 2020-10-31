#include "Servicio.h"
#include <string.h>
#include <string>
#include <fstream>
#include <dirent.h>


using namespace std;


Servicio::Servicio(){}

Servicio::Servicio(int _origen, string _fecha, int _turno)
{
    origen = _origen;
    fecha = _fecha;
    turno = _turno;
    filaA = "OOOOOOOOOOOOOOOOOOOO";
    filaB = "OOOOOOOOOOOOOOOOOOOO";
    filaC = "OOOOOOOOOOOOOOOOOOOO";
}

Servicio::~Servicio(){}

Servicio::Servicio(int _idServicio, int _origen, string _fecha, int _turno, string _filaA, string _filaB, string _filaC)
{
    idServicio = _idServicio;
    origen = _origen;
    fecha = _fecha;
    turno = _turno;
    filaA = _filaA;
    filaB = _filaB;
    filaC = _filaC;
}


void Servicio::setOrigen(int _origen)
{
    origen = _origen;
}

int Servicio::getOrigen()
{
    return origen;
}
void Servicio::setFecha(string _fecha)

{
    fecha = _fecha;
}

string Servicio::getFecha()
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

void Servicio::setfilaA(string _filaA)
{
    filaA = _filaA;
}

string Servicio::getfilaA()
{
    return filaA;
}

void Servicio::setfilaB(string _filaB)
{
    filaB = _filaB;
}

string Servicio::getfilaB()
{
    return filaB;
}

void Servicio::setfilaC(string _filaC)
{
    filaC = _filaC;
}

string Servicio::getfilaC()
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
    serv.setFecha(string(fecha));
    serv.setTurno(atoi(turno));

    string nombreArchivo = "servicios/" + serv.getFecha() + ".txt";
    fstream servicios;

    servicios.open(nombreArchivo, fstream::app);

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
            servicioAGuardar = serv.crearServicio();
            servicios << servicioAGuardar << endl;
            respuesta = 1;
        }

    }
    servicios.close();
    return respuesta;
}

void Servicio:: reservarAsiento(char *message){
    int resp = CrearServicio(message);
    if (resp == 1){
        cout << "servicio creado" << endl;
    }
    string p = "hasta aca llego";
    cout << p << endl;
}

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


list<Servicio> Servicio:: buscarServicioPorFecha(string fecha) {
    list<Servicio> lista;
    list<Servicio> :: iterator it = lista.begin();

    string _origen, _fecha, _turno, _filaA, _filaB, _filaC;
    string nombreArchivo = "servicios/" + string(fecha) + ".txt";
    ifstream servicios;

    servicios.open(nombreArchivo, fstream::in);

    if(!servicios)
    {
        cout<< "No se pudo abrir el archivo.";
    }
    //Siempre lo crea con el fstream pero por algun error se pone arriba, y aca sigue la logica
    else{
        cout<<"Se encontro archivo: "<<nombreArchivo<<endl;

        int cantidad = 0;
        while (!servicios.eof()) {
            getline(servicios, _origen, ';');
            if (_origen != "") {
                getline(servicios, _fecha, ';');
                getline(servicios, _turno, ';');
                getline(servicios, _filaA, ';');
                getline(servicios, _filaB, ';');
                getline(servicios, _filaC);

                cantidad++;
                Servicio *servicio = new Servicio(cantidad, stoi(_origen), _fecha, stoi(_turno), _filaA, _filaB, _filaC);
                lista.insert(it, *servicio);
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

