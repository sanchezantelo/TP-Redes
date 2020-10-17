#ifndef SOCKETSELECT_H
#define SOCKETSELECT_H


class SocketSelect {
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/wsapiref_2tiq.asp
  public:
    SocketSelect(Socket const * const s1, Socket const * const s2=NULL, TypeSocket type=BlockingSocket);

    bool Readable(Socket const * const s);

  private:
    fd_set fds_;
};


#endif // SOCKETSELECT_H
