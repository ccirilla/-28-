#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <memory>
#include <functional>


using namespace std;

class Noncopyable
{
protected:
    Noncopyable(){}
    Noncopyable(const Noncopyable &rhs) = delete;
    Noncopyable & operator = (const Noncopyable &rhs) = delete ;
};

class Thread
:Noncopyable
{
public:
    using threadCallback = function<void()>;
    void start();
    void join();
    ~Thread();
    Thread(threadCallback && func)
    : _cb(move(func))
    {}
private:
    static void* threadFunc(void *);
private:
    pthread_t _pthid = 0;
    bool _isRuning = false;
    threadCallback _cb;
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
    p->_cb();
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


class Mythread
{
public:
    void run()
    {
        srand(clock());
        int cnt = 10;
        while(cnt--)
        {
            cout << "sub thread : " << pthread_self()
                 << " get number = " << rand()%100 << endl;
            sleep(1);
        }
    }
    ~Mythread()
    {
        cout << "~Mythread()" << endl;
    }
};




int main()
{
    unique_ptr<Thread> mythread(new Thread(bind(&Mythread::run,Mythread())));
    mythread->start();
    mythread->join();
    return 0;
}

