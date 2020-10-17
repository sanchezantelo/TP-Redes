#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{
  Servidor *Server = new Servidor();
  while(true)
  {
     Server->Recibir();
     Server->Enviar();
  }
}
