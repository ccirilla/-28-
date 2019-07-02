#include "Timer.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <iostream>
using namespace std;


namespace wd
{

Timer::Timer(int initTime, int intervalTime,TimerCallback && cb)
    : _fd(createTimerfd())
      , _initalTime(initTime)
      , _intervalTime(intervalTime)
      , _isStarted(false)
      , _cb(move(cb))
    {}

Timer::~Timer()
{
    close(_fd);
}

void Timer::start()
{
    setTimer(_initalTime,_intervalTime);
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

void Timer::stop()
{
    if(_isStarted){
        _isStarted = false;
        setTimer(0,0);
    }
}

void Timer::setTimer(int initTime, int intervalTime)
{
    struct itimerspec value;
    value.it_value.tv_sec = initTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = intervalTime;
    value.it_interval.tv_nsec = 0;
    int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
    if(ret == -1) {
        perror(">> timerfd_settime");
    }
}

int Timer::createTimerfd()
{
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(fd == -1) {
        perror("timerfd_create");
    }
    return fd;
}

void Timer::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_fd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)) {
        perror(">> read");
    }
}

}
