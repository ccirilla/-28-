#ifndef __ID__
#define __ID__
#include "TaskQue.h"
#include <unistd.h>
#include <functional>
#include <memory>
using namespace std;

class Thread
:Noncopyable
{
public:
    ~Thread(){
        if(_isRuning){
            pthread_detach(_pthid);
            _isRuning = false;
        }
    }
    void start(){
        pthread_create(&_pthid,nullptr,ThreadFunc,this);
        _isRuning = true;
    }
    void join(){
        if(_isRuning){
            pthread_join(_pthid,nullptr);
            _isRuning = false;
        }
    }

private:
    virtual void run() = 0;
    static void* ThreadFunc(void* p){
        Thread * pthread = (Thread*)p;
        pthread->run();
        return nullptr;
    }
private:
    pthread_t _pthid = 0;
    bool _isRuning = false;
};



#endif
