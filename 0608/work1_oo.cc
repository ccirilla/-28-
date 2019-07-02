#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <memory>

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


class Mythread
:public Thread
{
    void run() override
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
    unique_ptr<Thread> mythread(new Mythread());
    mythread->start();
    mythread->join();
    return 0;
}

