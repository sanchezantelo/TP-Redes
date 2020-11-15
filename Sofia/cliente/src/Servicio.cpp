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


string Servicio::reservayliberaAsientos(char* _asientos, int cantAsientos)
{
    string totalARetornar;
    string asientos = string(_asientos);

    char *filaTotalARetornar;
    char *filaA = getfilaA();
    char *filaB = getfilaB();
    char *filaC = getfilaC();
    for(int i=0; i<cantAsientos;i++)
    {
        //veo si es de reservar o liberar
        //char asiento[4] = "";
        char asientoEntrante[14] = "";
        strcpy(asientoEntrante, asientos.c_str());
        //strcpy(asiento, strtok(asientoEntrante,"|"));

        int j = 0;
        int k = 1;
        int l = 3;

        if(i == 1)
        {
            j = 5;
            k = 6;
            l = 8;
        }
        if(i == 2)
        {
            j = 10;
            k = 11;
            l = 13;
        }
        char filaARetornar[21] = "";
        char tipo, fila, nroAsiento;
        fila = asientoEntrante[j];
        nroAsiento = asientoEntrante[k];
        tipo = asientoEntrante[l];
        if(tipo == 'x')
        {
            if(fila == 'A')
            {
                strcpy(filaARetornar,filaA);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    ocuparAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaARetornar, filaB), filaC );
            }
            else if(fila == 'B')
            {
                strcpy(filaARetornar,filaB);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    ocuparAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaA, filaARetornar), filaC );
            }
            else if(fila == 'C')
            {
                strcpy(filaARetornar,filaC);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    ocuparAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaA, filaB), filaC );
            }

        }
        else if(tipo == 'o')
        {
            if(fila == 'A')
            {
                strcpy(filaARetornar,filaA);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    liberarAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaARetornar, filaB), filaC );
            }
            else if(fila == 'B')
            {
                strcpy(filaARetornar,filaB);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    liberarAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaA, filaARetornar), filaC );
            }
            else if(fila == 'C')
            {
                strcpy(filaARetornar,filaC);
                if(asientoLibre(filaARetornar, nroAsiento))
                {
                    liberarAsiento(filaARetornar, nroAsiento);
                }
                filaTotalARetornar = strcat(strcat( filaA, filaB), filaARetornar );
            }

        }

        totalARetornar = filaTotalARetornar;
        //asientosAuxiliarString.erase(0,4);

    }

    return totalARetornar;
}

char* Servicio::reservarAsiento(char _asiento[1])
{
    //Obtengo la fila del asiento
    char *filaTotalARetornar;
    char filaARetornar[21] = "";

    char fila, nroAsiento;
    fila = _asiento[0];
    nroAsiento = _asiento[1];
    int nroAsientoEntero = int(nroAsiento) -1;
    // = nroAsientoEntero +'0';


    if(fila == 'A')
    {
        strcpy(filaARetornar,getfilaA());
        if(asientoLibre(filaARetornar, nroAsiento))
        {
            ocuparAsiento(filaARetornar, nroAsiento);
        }
        filaTotalARetornar = strcat(strcat( filaARetornar, getfilaB()), getfilaC() );
    }
    else if(fila == 'B')
    {
        strcpy(filaARetornar,getfilaB());
        if(asientoLibre(filaARetornar, nroAsiento))
        {
            ocuparAsiento(filaARetornar, nroAsiento);
        }
    }
    else if(fila == 'C')
    {
        strcpy(filaARetornar,getfilaC());
        if(asientoLibre(filaARetornar, nroAsiento))
        {
            ocuparAsiento(filaARetornar, nroAsiento);
        }
    }
    return filaTotalARetornar;
}

bool Servicio::asientoLibre(char _fila[21], char _numero)
{
    int numeroEntero = _numero - 48;
    numeroEntero = numeroEntero - 1;
    for(int i=0; i<21; i++)
    {
        if(i == numeroEntero)
        {
            if(_fila[i] == 'X')
            return false;
        }
    }
    return true;
}

void Servicio::ocuparAsiento(char _fila[21], char _numero)
{
    int numeroEntero = _numero - 48;
    numeroEntero = numeroEntero - 1;
    char *filaModificada = _fila;
    filaModificada[numeroEntero] = 'X';
    strcpy(_fila, filaModificada);
}

void Servicio::liberarAsiento(char _fila[21], char _numero)
{
    int numeroEntero = _numero - 48;
    numeroEntero = numeroEntero - 1;
    char *filaModificada = _fila;
    filaModificada[numeroEntero] = 'O';
    strcpy(_fila, filaModificada);
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
