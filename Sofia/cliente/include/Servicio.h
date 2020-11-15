#ifndef SERVICIO_H
#define SERVICIO_H
#include <iostream>
using namespace std;

class Servicio
{
    int idServicio;
    int origen;
    char fecha[11];
    int turno;
    char filaA[21];
    char filaB[21];
    char filaC[21];

    public:
        Servicio();
        Servicio(int _origen, char _fecha[21], int _turno);
        Servicio(int _idServicio, int _origen, char _fecha[21], int _turno, char _filaA[21], char _filaB[21], char _filaC[21]);
        virtual ~Servicio();
        void setOrigen(int _origen);
        int getOrigen();
        void setFecha(char _fecha[21]);
        char* getFecha();
        void setTurno(int _turno);
        int getTurno();
        void setfilaA(char _filaA[21]);
        char* getfilaA();
        void setfilaB(char _filaB[21]);
        char* getfilaB();
        void setfilaC(char _filaC[21]);
        char* getfilaC();
        void mostrar();
        void mostrarTexto();
        string mensaje();
        char* reservarAsiento(char _asiento[2]);
        bool asientoLibre(char _fila[21], char _numero);
        void ocuparAsiento(char _fila[21], char _numero);
        void liberarAsiento(char _fila[21], char _numero);
        string reservayliberaAsientos(char* _asientos, int cantAsientos);

    protected:

    private:
};

#endif // SERVICIO_H
