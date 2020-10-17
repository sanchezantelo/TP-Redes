#include <iostream>
#include <winsock2.h>
#include <Servidor.h>

using namespace std;

int main()
{
  Servidor *Server = new Servidor();
  while(true)
  {
     Server->LogServer();
     Server->Recibir();
     Server->Enviar();

  }
}
