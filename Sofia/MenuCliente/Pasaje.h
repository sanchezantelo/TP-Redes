#ifndef PASAJE_H
#define PASAJE_H
#include <string>

enum Origen{MAR_DEL_PLATA,BUENOS_AIRES};
enum Turno{MANANA,TARDE,NOCHE};
enum Asiento{SIMPLE,DOBLE};
using namespace std;
class Pasaje
{
    public:
        Origen origen;
         std::string fecha;
        Turno turno;
        Asiento asiento;
        Pasaje(Origen origen, string fecha,Turno turno, Asiento asiento);
        virtual ~Pasaje();

    protected:

    private:
};

#endif // PASAJE_H

