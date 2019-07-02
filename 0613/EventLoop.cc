#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
    addEpollFdRead(_acceptor.fd());        
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
        waitEpollFd();
}

void EventLoop::unloop()
{
    if(_isLooping)
        _isLooping = false;
}

void EventLoop::waitEpollFd()
{
    int readNum;
    do{
        readNum = epoll_wait(_efd,&*_eventList.begin(),
                             _eventList.size(),5000);
    }while( readNum == -1 && errno == EINTR );
    if(readNum == -1){
        perror("epoll_wait");
        return;
    }
    else if(readNum == 0){
        cout << ">> epoll_wait timeout!" << endl;
    }
    else
    {
        if(readNum == (int)_eventList.size()){
            _eventList.resize(2*readNum);
        }
        for(int idx = 0;idx != readNum;idx++)
        {
            int fd = _eventList[idx].data.fd;
            if(fd == _acceptor.fd()){
                if(_eventList[idx].events == EPOLLIN){
                    handleNewConnection();
                }
            }
            else{
                if(_eventList[idx].events == EPOLLIN){
                    handleMessage(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int fd = _acceptor.accept();
    addEpollFdRead(fd);
    TcpConnectionPtr temp(new TcpConnection(fd));
    temp->setCloseCallback(_onClose);
    temp->setMessageCallback(_onMessage);
    temp->setConnectionCallback(_onConnection);
    _conns[fd] = temp;
    temp->handleConnectionCallback();
}

bool EventLoop::isConnectionClosed(int fd)
{
    int ret;
    do{
        char buf[1024];
        ret = recv(fd,buf,sizeof(buf),MSG_PEEK);
    }while(ret == -1 && errno == EINTR);
    return (ret == 0);
}

void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    assert( it != _conns.end() );
    bool isClosed = isConnectionClosed(fd);
    if(isClosed)
    {
        delEpollFdRead(fd);
        it->second->handleCloseCallback();
        _conns.erase(fd);
    }else
    {
        it->second->handleMessageCallback();
    }
}

int EventLoop::createEpollFd()
{
    int ret = epoll_create1(0);
    if(ret == -1){
        perror("epoll_create1");
    }
    return ret;
}

void EventLoop::addEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&event) == -1){
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&event) == -1){
        perror("epoll_ctl");
    }
}

}

