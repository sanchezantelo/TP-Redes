#include <iostream>
#include <winsock2.h>
#include <Cliente.h>
using namespace std;

int main()
{
    Cliente *Client = new Cliente();
    while(true)
    {
        Client->Enviar();
        Client->Recibir();
    }
}
