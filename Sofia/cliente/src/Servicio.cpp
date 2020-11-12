#include "Servicio.h"
#include <string.h>

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
string Servicio::mensaje(){
    return to_string(getOrigen()) + ";" + getFecha() + ";" + to_string(getTurno());
}

void Servicio::mostrarTexto()
{
    char origen_string[3][20] = {"Buenos Aires", "Mar del Plata"};
    char turno_string[4][20] = {"Manana", "Tarde", "Noche"};
    int destino = getOrigen();

    if (getOrigen() == 1)
        destino++;
    else
        destino--;

    cout << origen_string[getOrigen() - 1] << " a " << origen_string[destino - 1] << " el " << getFecha() << " turno " << turno_string[getTurno() - 1] << endl;
}
