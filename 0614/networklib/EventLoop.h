#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__
#include "MutexLock.h"
#include <sys/epoll.h>
#include <map>
#include <memory>
#include <vector>
#include <functional>
using std::vector;
using std::map;
using std::shared_ptr;

namespace wd
{

class Acceptor;
class TcpConnection;

class EventLoop
{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using Functor = std::function<void()>;
public:
    EventLoop(Acceptor & acceptor);
    void loop();
    void unloop();
    void runInLoop(Functor && cb);
    void setConnectionCallback(TcpConnectionCallback && cb)
    {   _onConnection = std::move(cb);  }
    void setMessageCallback(TcpConnectionCallback && cb)
    {   _onMessage = std::move(cb); }
    void setCloseCallback(TcpConnectionCallback && cb)
    {   _onClose = std::move(cb); }
private:
    int createEpollFd();
    int createEventFd();
    void waitEpollFd();
    void addEpollFdRead(int);
    void delEpollFdRead(int);
    void handleRead();
    void handleNewConnection();
    bool isConnectionClosed(int fd);
    void handleMessage(int fd);
    void wakeup();
    void doPendingFunctors();
private:
    int _efd;
    int _eventfd;
    Acceptor & _acceptor;
    vector<struct epoll_event> _eventlist;
    map<int,TcpConnectionPtr> _conns;
    bool _isLooping;
    MutexLock _mutex;
    vector<Functor> _pendingFunctors;
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

}
#endif
