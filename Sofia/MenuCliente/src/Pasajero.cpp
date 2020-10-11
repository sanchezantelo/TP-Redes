#include "Pasajero.h"

Pasajero::Pasajero(Origen origen, string fecha,Turno turno, Asiento asiento){
        origen=origen;
        fecha=fecha;
        turno=turno;
        asiento=asiento;
        }

Pasajero::~Pasajero()
{
    //dtor
}
