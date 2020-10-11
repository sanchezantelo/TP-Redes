#include "Servicio.h"

Servicio::Servicio(int _origen, string _fecha, int _turno)
{
    origen = _origen;
    fecha = _fecha;
    turno = _turno;
    filaA = "OOOOOOOOOOOOOOOOOOOO";
    filaB = "OOOOOOOOOOOOOOOOOOOO";
    filaC = "OOOOOOOOOOOOOOOOOOOO";
}

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

Servicio::~Servicio()
{
    //dtor
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
