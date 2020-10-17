#include "SocketServer.h"

SocketServer::SocketServer(int port, int connections, TypeSocket type) {
  sockaddr_in sa;

  memset(&sa, 0, sizeof(sa));

  sa.sin_family = PF_INET;
  sa.sin_port = htons(port);
  s_ = socket(AF_INET, SOCK_STREAM, 0);
  if (s_ == INVALID_SOCKET) {
    throw "INVALID_SOCKET";
  }

  if(type==NonBlockingSocket) {
    u_long arg = 1;
    ioctlsocket(s_, FIONBIO, &arg);
  }

  /* bind the socket to the internet address */
  if (bind(s_, (sockaddr *)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
    closesocket(s_);
    throw "INVALID_SOCKET";
  }

  listen(s_, connections);
}

Socket* SocketServer::Accept() {
  SOCKET new_sock = accept(s_, 0, 0);
  if (new_sock == INVALID_SOCKET) {
    int rc = WSAGetLastError();
    if(rc==WSAEWOULDBLOCK) {
      return 0; // non-blocking call, no request pending
    }
    else {
      throw "Invalid Socket";
    }
  }

  Socket* r = new Socket(new_sock);
  return r;
}
