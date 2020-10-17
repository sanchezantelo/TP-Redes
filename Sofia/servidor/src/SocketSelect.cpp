#include "SocketSelect.h"

SocketSelect::SocketSelect(Socket const * const s1, Socket const * const s2, TypeSocket type) {
  FD_ZERO(&fds_);
  FD_SET(const_cast<Socket*>(s1)->s_,&fds_);
  if(s2) {
    FD_SET(const_cast<Socket*>(s2)->s_,&fds_);
  }

  TIMEVAL tval;
  tval.tv_sec  = 0;
  tval.tv_usec = 1;

  TIMEVAL *ptval;
  if(type==NonBlockingSocket) {
    ptval = &tval;
  }
  else {
    ptval = 0;
  }

  if (select (0, &fds_, (fd_set*) 0, (fd_set*) 0, ptval) == SOCKET_ERROR)
     throw "Error in select";
}

bool SocketSelect::Readable(Socket const* const s) {
  if (FD_ISSET(s->s_,&fds_)) return true;
     return false;
}
