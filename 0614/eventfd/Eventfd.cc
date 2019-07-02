#include "Eventfd.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <iostream>
#include <sys/eventfd.h>
using namespace std;


namespace wd
{

Eventfd::Eventfd(EventfdCallback && cb)
    : _fd(createEventfd())
      , _isStarted(false)
      , _cb(move(cb))
    {}

Eventfd::~Eventfd()
{
    close(_fd);
}

void Eventfd::start()
{
    _isStarted = true;
    int efd = epoll_create1(0);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = _fd;
    epoll_ctl(efd,EPOLL_CTL_ADD,_fd,&event);
    while(_isStarted)
    {
        int readNum;
        readNum = epoll_wait(efd,&event,1,5000);
        if(readNum == -1 && errno == EINTR)
            continue;
        else if(readNum == -1){
            perror("epoll_wait");
            return;
        } else if(readNum == 0){
            cout << ">> poll timeout " << endl;
        } else{
            handleRead();
            if(_cb){
                _cb();
            }
        }
    }
}

void Eventfd::stop()
{
    if(_isStarted){
        _isStarted = false;
    }
}


int Eventfd::createEventfd()
{
    int fd = ::eventfd(10, 0);
    if(fd == -1) {
        perror("eventfd");
    }
    return fd;
}

void Eventfd::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_fd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)) {
        perror(">> read");
    }
}

void Eventfd::wakeup()
{
    uint64_t one = 1;
    int ret = write(_fd,&one,sizeof(one));
    if(ret != sizeof(one)){
        perror(">> write");
    }
}

}
