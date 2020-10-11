#ifndef PASAJERO_H
#define PASAJERO_H
#include <string>
enum Origen{MAR_DEL_PLATA,BUENOS_AIRES};
enum Turno{MANANA,TARDE,NOCHE};
enum Asiento{SIMPLE,DOBLE};
using namespace std;
class Pasajero
{
    public:
        Origen origen;
         std::string fecha;
        Turno turno;
        Asiento asiento;
        Pasajero(Origen origen, string fecha,Turno turno, Asiento asiento);
        virtual ~Pasajero();

    protected:

    private:
};

#endif // PASAJERO_H
