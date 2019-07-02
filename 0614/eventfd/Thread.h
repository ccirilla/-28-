#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>
#include "Noncopyable.h"

namespace wd
{

using ThreadCallback = std::function<void()>;

class Thread
:Noncopyable
{
public:
    Thread(ThreadCallback && cb)
    : _cb(std::move(cb))
    {}
    ~Thread();
    void start();
    void join();
private:
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    bool _isRunning = false;
    ThreadCallback _cb;
};

}
#endif
