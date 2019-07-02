#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "InetAddress.h"
#include "Socket.h"

namespace wd
{

class Acceptor
{
public:
    Acceptor(unsigned short port);
    Acceptor(const string & ip, unsigned short port);
    void ready();
    int accept();
    int fd()const;
private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();
private:
    Socket _listensock;
    InetAddress _addr;
};

}

#endif
