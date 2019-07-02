#include "Thread.h"
#include <errno.h>

namespace wd
{
    
Thread::~Thread()
{
    if(_isRunning){
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

void Thread::start()
{
    if(pthread_create(&_pthid,nullptr,threadFunc,this) == -1){
        perror("pthread_create");
        return;
    } else{
        _isRunning = true;
    }
}

void Thread::join()
{
    if(_isRunning){
        pthread_join(_pthid,nullptr);
        _isRunning = false;
    }
}

void* Thread::threadFunc(void *arg)
{
    Thread* pthread = (Thread*) arg;
    if(pthread->_cb){
        pthread->_cb();
    }
    return nullptr;
}

}

