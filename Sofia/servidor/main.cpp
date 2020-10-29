#include <iostream>
#include <winsock2.h>
#include <Servidor.h>
#include <Servicio.h>
#include <dirent.h>
using namespace std;

int CrearServicio(char * message);
int buscarServicio(char * message);
list<Servicio> buscarServicioPorFecha(string fecha);
list<Servicio> buscarServicioPorOrigen(list<Servicio> lista, int origen);
list<Servicio> buscarServicioPorTurno(list<Servicio> lista, int turno);
bool ServicioExiste(Servicio servicio);

int main()
{
    while(true){
      Servidor *server = new Servidor();
      bool logueado = false;

      while(server->sesion() && !server->LogOutPorTimeOut())
      {
         char message[100] = "";
         if (!logueado)
            server->Enviar("ok");
         string recibido = server->Recibir();

         if(recibido.find("login")==0){
            if(server->Login()==true){
                server->Enviar("autenticado");
                logueado = true;
            }else{
                server->Enviar("no autorizado");
                logueado = false;
               // server->CerrarSocket();
                }
            }


         if(server->LogOutPorTimeOut()){
            server->CerrarSocket();
            server->~Servidor();
            system("PAUSE");
         }
         if(recibido.find("MostrarActividad")==0){
            server->Enviar(server->mostrarActividades(recibido));
         }



         if(recibido.find("G1") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            int respuesta = CrearServicio(message);
            server->Enviar(to_string(respuesta));
         }

         if(recibido.find("G2") == 0){
            strcpy(message, recibido.erase(0,3).c_str());
            int respuesta = buscarServicio(message);
            server->Enviar(to_string(respuesta));
         }

         if(server->LogOut()){
            server->Enviar("Sesion cerrada");
            server->CerrarSocket();
            system("PAUSE");
            break;
         }

      }
      server->~Servidor();
      }
}


int CrearServicio(char * message)
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

int buscarServicio(char * message) {
    int respuesta = 0;
    char c_origen[5] = "";
    char fecha[15] = "";
    char c_turno[5] = "";

    strcpy(c_origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(c_turno, strtok(NULL, ";"));

    int origen = atoi(c_origen);
    int turno = atoi(c_turno);

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

    // Hay que devolverlo al cliente
    for (it = listaServicios.begin(); it != listaServicios.end(); ++it) {
        lst = lst + to_string(((Servicio)* it).getOrigen()) + ";" + ((Servicio)* it).getFecha() + ";" + to_string(((Servicio)* it).getTurno()) + "|\n";
        cout << lst << endl;
    }

    return respuesta;
}

list<Servicio> buscarServicioPorFecha(string fecha) {
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

list<Servicio> buscarServicioPorOrigen(list<Servicio> lista, int origen) {
    list<Servicio> :: iterator it = lista.begin();

    for (it = lista.begin(); it != lista.end(); ++it) {
        if (((Servicio)* it).getOrigen() != origen) {
            it = lista.erase(it);
            --it;
        }

    }

    return lista;
}

list<Servicio> buscarServicioPorTurno(list<Servicio> lista, int turno) {
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
bool ServicioExiste(Servicio servicio)
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
