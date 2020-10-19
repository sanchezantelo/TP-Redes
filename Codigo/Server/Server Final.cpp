#include <stdio.h>
#include <winsock2.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <time.h>
#include <Windows.h>
#include "../Funciones/Funciones.h"
#define PORT 54321
#define IP "127.0.0.1"
#include <Servicio.h>
#include <cstdlib>
#include <ctype.h>
bool recibido = false; //variable global para usarlas con hilos.

using namespace std;

bool Login(char* usuario, char* password);
void* recibir(void *sockClient);
bool contar(int segundos);
char* recibir_y_contar(SOCKET sock);
void GetMessageFromCliente(SOCKET sock, char *message);
int CrearServicio(char *message);
bool ServicioExiste(Servicio servicio);
char* valueOfOrigen(char* origen_in);
char* valueOfTurno(char* turno_in);
void lowstr(char *s);


int main(int arg, char** argv){
    //INICIALIZAR UN SOCKET
    SOCKET sockServer = crearSocket();
    //-----------------------------------------------------------------------------------------------------
    //CREAR ESTRUCTURA Y UNIR LOS DATOS DEL SOCKET CON BIND
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; //Le decimos que use ipv4.
    sin.sin_addr.s_addr = inet_addr(IP); //Direccion ip de la cual escuchará el servidor.
    sin.sin_port = htons(PORT); //Puerto del cual escuchara el servidor
    memset(sin.sin_zero,0,sizeof(sin.sin_zero)); //RELLENO ( arreglo de 8 bytes que SIEMPRE debera ser llenado con ceros por cuestiones problematicas...)

    bind(sockServer,(struct sockaddr*)&sin, sizeof(sin)); //Al socket sockServer le agregamos datos (ip y puerto)
    //----------------------------------------------------------------------------------------------------------
    //EMPEZAR A ESCUCHAR LISTEN
    listen(sockServer,0);

    //BUCLE INFINITO PARA ACEPTAR INFINITOS USUARIOS
    while(true){
        //bucle de un cliente en concreto, cuando el cliente ponga cerrar sesion o haga 3 intentos
        //fallidos o pasen 2 min, entonces se saldra del bucle.
        new_client: //el cliente se puede desconectar en cualquier parte del programa, asique lo mejor fue usar goto para volver al inicio
        bool desconectar = false;
        while(!desconectar){
            struct sockaddr_storage addrstorage; //storage es para guardar los datos del cliente que se va a conectar.
            int length = sizeof(addrstorage); //ya que no sabes el tamaño de la conexion del cliente (ipv4, ipv6 u otro), necesitamos hacer un sizeof.
            //system("cls");
            printf("Esperando a un cliente...");
            SOCKET sockClient = accept(sockServer,(struct sockaddr*)&addrstorage,&length); //"en el socket sockServer, acepto la conexion proveniente de un cliente X
            //y voy a guardar los datos del cliente en addrstorage. Luego les devuelvo un socket del cliente para que puedan comunicarse entre ustedes que llamamos sockClient"
            system("cls");
            printf("Cliente Encontrado!.\n");

            //RECIBIMOS USUARIO Y CONTRASEÑA:
            char *user = NULL, *pass = NULL, respuesta[3] = "", *altaServicioRespuesta = NULL;
            bool salir = false;
            int numeroIntentos = 0;
            //Se sale del bucle cuando el cliente ingrese bien el usuario y contraseña o halla fallado 3 veces
            do {
                printf("\nEsperando Ingreso de usuario y contrase%ca...", 164);

                user = recibir_y_contar(sockClient); //recibo el usuario que escribio el cliente
                if(user == NULL) goto new_client;

                pass = recibir_y_contar(sockClient); //recibo la contraseña que escribio el cliente
                if(user == NULL) goto new_client;

                //COMPROBAMOS EL USUARIO Y CONTRASEÑA EN credenciales.txt:
                if( Login(user, pass) )
                {
                    cout<<"\nLogin Correcto. Cliente Conectado."<<endl;
                    strcpy(respuesta, "OK");
                    enviar(sockClient,respuesta, 2); //envio el texto "OK" al cliente
                    salir = true;

                }
                else
                {
                    cout << "\nUsuario o contrase\xA4"<< "a incorrectos." << endl;
                    strcpy(respuesta, "NO");
                    enviar(sockClient,respuesta, 2); //envio el texto "NO" al cliente
                    numeroIntentos++;
                    if(numeroIntentos == 3){
                        salir = true;
                        desconectar = true;
                        cout << "\nMaximo de intentos permitidos. Desconectando cliente...";
                    }
                }

            } while(!salir);

            //altaServicioRespuesta = recibir_y_contar(sockClient);
            //CLIENTE CONECTADO!!!
            //ACA HAGAN LA LOGICA DE SUS PROGRAMAS QUE TIENEN QUE HACER USTEDES!

            //-------------------ALTA-SERVICIO--------------------//

                    //modificar para obtener el message desde el cliente
                    char messagePrueba[1000] = "Mar del Plata;2020-05-24;Tarde";
                    int respuestaAltaServicio = CrearServicio(messagePrueba);
                    if(respuestaAltaServicio = 1)
                    {
                        cout<<"Servicio creado con Exito"<<endl;
                        //Devolver servicio creado con exito al usuario
                    }
                    else if(respuestaAltaServicio = 2)
                    {
                        cout<<"Servicio ya existe"<<endl;
                        //Devolver servicio ya existente al usuario
                    }
                    else{
                        cout<<"Error al crear servicio"<<endl;
                        //Devolver mensaje error al crear servicio al usuario
                    }
            //-----------------------------------------------------//

            //FALTA!! ACA SOFIA TENES QUE SETEAR LA VARIABLE desconectar a TRUE cuando el cliente aprete "cerrar sesion"
            //TENES QUE HACER LA LOGICA.
            printf("\n\nNo apretes ninguna tecla porque se resetea a esperar a un nuevo cliente (sofia te toca esta parte que es la de cerrar sesion).");
            system("pause>nul");

        } //ACA TERMINA EL BUCLE DE UN CLIENTE EN CONCRETO

    }//ACA TERMINA EL BUCLE INFINITO PARA BUSCAR INFINITOS CLIENTES
}

bool Login(char* usuario, char* password)
{
    //VARIABLE QUE SE VA A DEVOLVER TRUE SI EL USUARIO Y PASSWORD ESTAN OK, Y FALSE SI NO LO ESTA
    bool respuesta = false;
    //VARIABLE DEL ARCHIVO Y OPEN DEL MISMO
    ifstream credenciales;
    credenciales.open("credenciales.txt",ios::in);

    //CHECK SI NO EXISTE ARCHIVO ARROJA ERROR
    if(credenciales.fail())
    {
        cerr << "\n\nError al abrir el archivo" << endl;
        exit(1);
    }
    //VARIABLES QUE SE VAN A UTILIZAR PARA RECORRER EL ARCHIVO
    string storedUser;
    string storedPass;
    //PASAJE DE PARAMETROS, RECORRE ARCHIVO Y CHECKEA
    while(credenciales >> storedUser >> storedPass)
    {
        //SI EL USUARIO Y EL PASSWORD SON LOS MISMOS RESPUESTA = TRUE
        if(storedUser == string(usuario) && storedPass == string(password))
        {
        respuesta = true;
        }
    }
    return respuesta;
}

//contar() cuenta los segundos pasados por parametro, si llega a la cantidad dada de segundos
//o la variable global "recibido" se vuelve true, entonces sale de la funcion.
bool contar(int segundos)
{
    //retorna verdadero si se cumplio el ciclo o falso si se interrumpio por la variable global.
  time_t inicio = time(NULL);;
  int tiempo = 0;
  bool desconectar = false;
  do {
    tiempo = difftime(time(NULL),inicio);
    if(tiempo == segundos) //Cuando pasen X segundos saldra del bucle.
        desconectar = true;
    Sleep(800); //espero 800ms para que no ocupe todo el procesador.
  }while(!desconectar && !recibido);
  return desconectar;
}
//recibir() esta funcion es ejecutada por un hilo y espera por un mensaje del cliente, si recibe un mensaje,
//retorna ese mensaje,caso contrario si esta funcion es cancelada por timeout o cierre de socket, devuelve la variable vacia.
void* recibir(void *sockClient){
    recibido = false;
    int n = 1000; //cantidad de bytes que voy a recibir.
    char *mensaje = (char*)calloc(n, sizeof(char));
    recv((SOCKET)sockClient, mensaje,n,0); //recibo el usuario que escribio el cliente y lo guardo en user.
    recibido = true;  //variable global para indicarle al main que deje de contar.
    pthread_exit((void*)mensaje);
}


//recibirContar() crea un hilo en donde hace 2 cosas en paralelo, cuenta tiempo y tambien
//espera por mensajes entrantes por parte del cliente. Recibe como parametro el socket del cliente y
//retorna un PUNTERO char, que contiene el mensaje recibido por el cliente si es que el cliente envio algo,
//de lo contrario retornara NULL. El mensaje tiene un tamaño maximo de 1000 bytes.
char* recibir_y_contar(SOCKET sock)
{
    char *mensaje = NULL;
    pthread_t hilo;
    bool timeout = false;
    pthread_create(&hilo, NULL, recibir, (void *)sock); //se empieza a ejecutar el hilo
    if(contar(10)) { //Cuento 120 segundos (2 min)
        printf("\n\nTimeout. Cliente desconectado.\n\n");
        closesocket(sock); //cierro el socket con el cliente (Aca el hilo deja de estar en recv y termina su ejecucion)
        pthread_join(hilo, NULL); //aca el hilo y el main se vuelven en uno solo.
        timeout = true;
    }
    if(!timeout) pthread_join(hilo, (void**)&mensaje); //termina el hilo (correctamente) y recupero el valor devuelto.
    return mensaje;
}

int CrearServicio(char * message)
{
    /**si respuesta = 1 servicio creado con exito
    *               = 2 servicio ya existe
    *               = 3 error al crear servicio
    */
    int respuesta = 0;
    Servicio serv= Servicio(1,"",1);
    char origen[100] = "";
    int origenEntero = 0;
    char fecha[100] = "";
    string fechaString;
    char turno[100] = "";
    int turnoEntero = 0;

    string servicio = string(message);
    string servicioAGuardar;
    //se divide el mensaje en diferentes variables a traves del delimitador
    strcpy(origen, strtok(message , ";"));
    strcpy(fecha, strtok(NULL, ";"));
    strcpy(turno, strtok(NULL, ";"));

    origenEntero = atoi(valueOfOrigen(origen));
    fechaString = string(fecha);
    turnoEntero = atoi(valueOfTurno(turno));

    //setea variables del servicio
    serv.setOrigen(origenEntero);
    serv.setFecha(fechaString);
    serv.setTurno(turnoEntero);

    char nombreArchivo[] = "servicios.txt";
    fstream servicios;

    servicios.open(nombreArchivo, fstream::in | fstream::out | fstream::app);

    //Si no existe, arroja error
    if(!servicios)
    {
        cout<< "No se pudo abrir el archivo.";
        respuesta = 3;
    }
    //Siempre lo crea con el fstream pero por algun error se pone arriba, y aca sigue la logica
    else{
        cout<<"Se encontro archivo: "<<nombreArchivo<<endl;

        //Variable para usar de parametro en el archivo y buscar si ya existe un servicio con el parametro de entrada
        string storedServicio;

        //to-do comparar si ya existe un servicio
        if(ServicioExiste(serv))
        {
        respuesta = 2;
        }

        else
        {
        servicioAGuardar = serv.crearServicio();
        servicios<<servicioAGuardar<<endl;
        respuesta = 1;
        }

    }
    return respuesta;
}
//to-do
bool ServicioExiste(Servicio servicio)
{
    return false;
}

char* valueOfOrigen(char* origen_in)
{
    /**retorna 1 si origen_in = "buenos aires"
    *          2 si origen_in = "mar del plata"
    */

    //Convierto a minuscula para no tener problema a como me llegue el mensaje
    lowstr(origen_in);
    char* keyBA = (char*)"buenos aires";
    char* keyMP = (char*)"mar del plata";
    char* respuesta = (char*)"";
    if(strcmp(keyBA, origen_in) == 0)
    {
        respuesta = (char*)"1";
    }
    else if(strcmp(keyMP, origen_in) == 0)
    {
        respuesta = (char*)"2";
    }
    return respuesta;
}

char* valueOfTurno(char* turno_in)
{
    /**retorna 1 si turno_in = "maniana"
    *          2 si turno_in = "tarde"
    *          3 si turno_in = "noche"
    */

    //Convierto a minuscula para no tener problema a como me llegue el mensaje
    lowstr(turno_in);
    char* keyM = (char*)"maniana";
    char* keyT = (char*)"tarde";
    char* keyN = (char*)"noche";
    char* respuesta = (char*)"";

    if(strcmp(keyM, turno_in) == 0)
    {
        respuesta = (char*)"1";
    }
    else if(strcmp(keyT, turno_in) == 0)
    {
        respuesta = (char*)"2";
    }
    else if(strcmp(keyN, turno_in) == 0)
    {
        respuesta = (char*)"3";
    }
    return respuesta;
}

void lowstr(char *s)
{
    //Convierte char a minuscula
    char *p;
    for(p = s; *p != '\0'; p++)
    {
        *p = (char) tolower(*p);
    }
}
