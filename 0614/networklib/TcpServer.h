#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace wd
{

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;

class TcpServer
{
public:
    TcpServer(const string & ip,unsigned short port)
    : _acceptor(ip,port)
    , _loop(_acceptor)
    {}
    void start(){
        _acceptor.ready();
        _loop.loop();
    }
    void setConnectionCallback(TcpConnectionCallback && cb){
        _loop.setConnectionCallback(move(cb));
    }
    void setMessageCallback(TcpConnectionCallback && cb){
        _loop.setMessageCallback(move(cb));
    }
    void setCloseCallback(TcpConnectionCallback && cb){
        _loop.setCloseCallback(move(cb));
    }
private:
    Acceptor _acceptor;
    EventLoop _loop;
};

}

#endif
