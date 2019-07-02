#include "EventLoop.h" 
#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <assert.h>
#include <sys/eventfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventFd())
, _acceptor(acceptor)
, _eventlist(1024)
, _isLooping(false)
{
    addEpollFdRead(_acceptor.fd());
    addEpollFdRead(_eventfd);
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    if(_isLooping){
        _isLooping = false;
    }
}

void EventLoop::runInLoop(Functor && cb)
{
    {
        MutexLockGuard autolock(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    wakeup();
}

void EventLoop::wakeup()
{
    uint64_t howmany;
    int ret = write(_eventfd,&howmany,sizeof(howmany));
    if(ret != sizeof(howmany)){
        perror("read");
    }
}

void EventLoop::waitEpollFd()
{
    int readNum;
    do{
        readNum = epoll_wait(_efd,&*_eventlist.begin(),_eventlist.size(),5000);
    }while(readNum == -1 && errno == EINTR);
    if(readNum == -1){
        perror("epoll_wait");
        return;
    } else if(readNum == 0){
        cout << ">> epoll_wait timeout!" << endl;
    } else 
    {
        if(readNum == (int)_eventlist.size()){
            _eventlist.resize(2*readNum);
        }
        for(int idx = 0;idx != readNum;idx++)
        {
            int fd = _eventlist[idx].data.fd;
            if(fd == _acceptor.fd()){
                if(_eventlist[idx].events & EPOLLIN){
                    handleNewConnection();
                }
            } else if(fd == _eventfd){
                if(_eventlist[idx].events & EPOLLIN){
                    handleRead();
                    doPendingFunctors();
                }
            } else 
            {
                if(_eventlist[idx].events & EPOLLIN){
                    handleMessage(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int peerfd = _acceptor.accept();
    addEpollFdRead(peerfd);
    TcpConnectionPtr conn(new TcpConnection(peerfd,this));
    conn->setConnectionCallback(_onConnection);
    conn->setMessageCallback(_onMessage);
    conn->setCloseCallback(_onClose);
    conn->handleConnectionCallback();
    _conns[peerfd] = std::move(conn);
}

void EventLoop::handleRead()
{
    uint64_t howmany;
    int ret = read(_eventfd,&howmany,sizeof(howmany));
    if(ret != sizeof(howmany)){
        perror("read");
    }
}

void EventLoop::doPendingFunctors()
{
    vector<Functor> temp;
    {
        MutexLockGuard autolock(_mutex);
        temp.swap(_pendingFunctors);
    }
    for(auto &functor: temp){
        functor();
    }
}

void EventLoop::handleMessage(int fd)
{
    bool isClosed = isConnectionClosed(fd);
    auto iter = _conns.find(fd);
    assert(iter != _conns.end());
    if(!isClosed){
        iter->second->handleMessageCallback();
    } else
    {
        delEpollFdRead(fd);
        iter->second->handleCloseCallback();
        _conns.erase(fd);
    }
}

bool EventLoop::isConnectionClosed(int fd)
{
    int ret;
    char buf[1024] = {0};
    do{
        ret = recv(fd,buf,sizeof(buf),MSG_PEEK);
    }while(ret == -1 && errno == EINTR);
    return (ret == 0);
}

int EventLoop::createEpollFd()
{
    int ret = ::epoll_create1(0);
    if(ret == -1){
        perror("epoll_create1");
    }
    return ret;
}

int EventLoop::createEventFd()
{
    int ret = eventfd(0,0);
    if(ret == -1){
        perror("eventfd");
    }
    return ret;
}

void EventLoop::addEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &event);
    if(-1 == ret){
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &event);
    if(-1 == ret){
        perror("epoll_ctl");
    }
}

}
