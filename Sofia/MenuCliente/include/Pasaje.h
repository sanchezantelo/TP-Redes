#ifndef PASAJE_H
#define PASAJE_H
#include <string>

class Pasaje
{
    public:
        Pasaje();
        Pasaje(std::string origen="",std::string fecha="",std::string turno="",std::string asiento="");
        virtual ~Pasaje();

        std::string Getorigen() { return origen; }
        void Setorigen(std::string val) { origen = val; }
        std::string Getfecha() { return fecha; }
        void Setfecha(std::string val) { fecha = val; }
        std::string Getturno() { return turno; }
        void Setturno(std::string val) { turno = val; }
        std::string Getasiento() { return asiento; }
        void Setasiento(std::string val) { asiento = val; }

    protected:

    private:
        std::string origen;
        std::string fecha;
        std::string turno;
        std::string asiento;
};

#endif // PASAJE_H
