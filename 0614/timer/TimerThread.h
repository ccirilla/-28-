#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__
#include "Timer.h"
#include "Thread.h"
             
namespace wd
{



class TimerThread
{
public:
    TimerThread(int initTime, int intervalTime,TimerCallback && cb)
    : _timer(initTime,intervalTime,std::move(cb))
    , _thread(bind(&Timer::start,&_timer))
    {}
    void start()
    {
        _thread.start();    
    }
    void stop(){
        _timer.stop();
        _thread.join();
    }
private:
    Timer _timer;
    Thread _thread;
};

}

#endif
