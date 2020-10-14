#include "Pasaje.h"

Pasaje::Pasaje(std::string origen,std::string fecha,std::string turno,std::string asiento)
{
    this->origen=origen;
    this->fecha=fecha;
    this->turno=turno;
    this->asiento=asiento;
}

Pasaje::~Pasaje()
{
    //dtor
}
