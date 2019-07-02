#include "TcpConnection.h"
#include "InetAddress.h"
#include "EventLoop.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>

namespace wd
{

TcpConnection::TcpConnection(int fd,EventLoop * loop)
    : _sock(fd)
      , _socketIo(fd)
      , _localAddr(getLocalAddr())
      , _peerAddr(getPeerAddr())
      , _isShutdwonWrite(false)
      , _loop(loop)
    {}

TcpConnection::~TcpConnection()
{
    if(!_isShutdwonWrite){
        shutdown();
    }
}

void TcpConnection::shutdown()
{
    if(!_isShutdwonWrite){
        _isShutdwonWrite = true;
        _sock.shutdownWrite();
    }
}

string TcpConnection::receive()
{
    char buf[65536] = {0};
    _socketIo.readline(buf,sizeof(buf));
    return string(buf);
}

void TcpConnection::send(const string & msg)
{
    _socketIo.writen(msg.c_str(),msg.size());
}

void TcpConnection::sendInLoop(const string & msg)
{
    _loop->runInLoop(bind(&TcpConnection::send,this,msg));
}

string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss << _localAddr.ip() << ":" << _localAddr.port() << " --> "
        << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getsockname(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getpeername(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
        perror("getpeername");
    }
    return InetAddress(addr);
}

}

