#include <iostream>
#include <fstream>
#include <sstream>
#include<ostream>
#include <Servicio.h>

using namespace std;

list<Servicio> buscarServicioPorFecha(string fecha,list<Servicio> &lista);
void ImprimirlstServicios(list<Servicio> &listaServicios);

int main()
{
    int option=1;

    do{
    string nombreArchivo="";
    cout << "Ingrese nombre del servicio a mostrar: " << endl;
    cin>>nombreArchivo;

    Servicio *servcio= new Servicio();


    servcio->buscarServicioPorFecha(nombreArchivo);

    cout<<"Seguir consultando 1. Salir 2."<<endl;
    cin>>option;
    system("cls");

    }while(option==1);

    return 0;
}


