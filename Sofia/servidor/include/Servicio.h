#ifndef SERVICIO_H
#define SERVICIO_H
#include <iostream>
#include"list"

using namespace std;

class Servicio
{
    int idServicio;
    int origen;
    string fecha;
    int turno;
    string filaA;
    string filaB;
    string filaC;

    public:
        Servicio();
        Servicio(int _origen, string _fecha, int _turno);
        Servicio(int idServicio, int _origen, string _fecha, int _turno, string _filaA, string _filaB, string _filaC);
        virtual ~Servicio();
        void setOrigen(int _origen);
        int getOrigen();
        void setFecha(string _fecha);
        string getFecha();
        void setTurno(int _turno);
        int getTurno();
        void setfilaA(string _filaA);
        string getfilaA();
        void setfilaB(string _filaB);
        string getfilaB();
        void setfilaC(string _filaC);
        string getfilaC();
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


    protected:

    private:
};

#endif // SERVICIO_H
