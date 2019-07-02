#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <memory>
#include "TaskQue.h"

using namespace std;

class Thread
:Noncopyable
{
public:
    void start();
    void join();
    virtual ~Thread();
private:
    static void* threadFunc(void *);
    virtual void run() = 0;
private:
    pthread_t _pthid = 0;
    bool _isRuning = false;
};

void Thread::start()
{
    if(pthread_create(&_pthid,nullptr,threadFunc,(void*)this))
        perror("pthread_create");
    _isRuning = true;
}

void* Thread::threadFunc(void *pthread)
{
    Thread *p = static_cast<Thread*>(pthread);
    p->run();
    return nullptr;
}

void Thread::join()
{
    if(_isRuning)
        pthread_join(_pthid,nullptr);
    _isRuning = false;
}

Thread::~Thread()
{
    if(_isRuning){
        pthread_detach(_pthid);
        _isRuning = false;
    }
    cout << "~Thread()" << endl;
}


class Producter
:public Thread
{
public:
    Producter(TaskQue & task)
    :Thread()
    , _task(task)
    {}
private:
    void run() override
    {
        int cnt = 0;
        while(1)
        {
            _task.push(++cnt);
            cout << "Producter thread : " << pthread_self()
                 << " produce  = " << cnt << endl;
            sleep(1);
        }
    }
private:
    TaskQue & _task;
};


class Consumer
:public Thread
{
public:
    Consumer(TaskQue & task)
    :Thread()
    , _task(task)
    {}
private:
    void run() override
    {
        while(1)
        {
            sleep(1);
            int cnt = _task.pop();
            cout << "Consumer thread : " << pthread_self()
                 << " consume  = " << cnt << endl;
        }
    }
private:
    TaskQue & _task;
};


int main()
{
    TaskQue task(10);
    unique_ptr<Thread> producter(new Producter(task));
    unique_ptr<Thread> consumer(new Consumer(task));
    unique_ptr<Thread> producter1(new Producter(task));
    producter->start();
    consumer->start();
    producter1->start();
    producter->join();
    consumer->join();
    producter1->join();
    return 0;
}

