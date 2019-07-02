#include "TcpConnection.h"
#include "InetAddress.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sstream>

namespace wd
{

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIo(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
, _isShutdwonWrite(false)
{}

TcpConnection::~TcpConnection()
{
    if(!_isShutdwonWrite)
        shutdown();
}

string TcpConnection::receive()
{
    char buf[65536] = {0};
    _socketIo.readline(buf,sizeof(buf));
    return string(buf);
}

void TcpConnection::send(const string &msg)
{
    _socketIo.writen(msg.c_str(),msg.size());
}

string TcpConnection::toString()const
{
    std::stringstream ss;
    ss << _localAddr.ip() << ":" << _localAddr.port()
       << "-->" << _peerAddr.ip() << ":" << _peerAddr.port();
    return ss.str();
}

void TcpConnection::shutdown()
{
    if(!_isShutdwonWrite)
    {
        _isShutdwonWrite = true;
        _sock.shutdownWrite();
    }
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in temp;
    socklen_t len = sizeof(struct sockaddr);
    if(getsockname(_sock.fd(),(struct sockaddr*)&temp,&len) ==-1)
    {
        perror("getsockname");
    }
    return InetAddress(temp);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in temp;
    socklen_t len = sizeof(struct sockaddr);
    if(getpeername(_sock.fd(),(struct sockaddr*)&temp,&len) ==-1)
    {
        perror("getpeername");
    }
    return InetAddress(temp);
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
    _onConnection = std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
        _onMessage = std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
        _onClose = std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
    if(_onConnection) {
        _onConnection(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage) {
        _onMessage(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose) {
        _onClose(shared_from_this());
    }
}

}


