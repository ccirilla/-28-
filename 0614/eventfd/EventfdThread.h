#ifndef __EventfdTHREAD_H__
#define __EventfdTHREAD_H__
#include "Eventfd.h"
#include "Thread.h"
             
namespace wd
{



class EventfdThread
{
public:
    EventfdThread(EventfdCallback && cb)
    : _Eventfd(std::move(cb))
    , _thread(bind(&Eventfd::start,&_Eventfd))
    {}
    void start()
    {
        _thread.start();    
    }
    void stop(){
        _Eventfd.stop();
        _thread.join();
    }
    void wakeup(){
        _Eventfd.wakeup();
    }
private:
    Eventfd _Eventfd;
    Thread _thread;
};

}

#endif
