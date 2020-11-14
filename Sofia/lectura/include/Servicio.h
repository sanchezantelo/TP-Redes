#ifndef SERVICIO_H
#define SERVICIO_H
#include <iostream>
#include"list"
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
        char* mensaje();
        string crearServicio();
        int CrearServicio(char * message);
        string buscarServicio(char * message);
        list<Servicio> buscarServicioPorFecha(string fecha);
        list<Servicio> buscarServicioPorOrigen(list<Servicio> lista, int origen);
        list<Servicio> buscarServicioPorTurno(list<Servicio> lista, int turno);
        bool ServicioExiste(Servicio servicio);
        string reservarAsiento(char *message);
        string encontradoServicio(char *message);


    protected:

    private:
};

#endif // SERVICIO_H
