#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H


class SocketServer : public Socket {
public:
  SocketServer(int port, int connections, TypeSocket type=BlockingSocket);

  Socket* Accept();
};


#endif // SOCKETSERVER_H
