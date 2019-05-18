#include <unistd.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;
int num = 10;


class MutexLock
{
public:
    MutexLock()
    {
        cout << "Mutex Init " << endl;
        pthread_mutex_init(&_mutex,NULL);
    }
    ~MutexLock()
    {
        cout << "Mutex Destory " << endl;
        pthread_mutex_destroy(&_mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t * getMutex()
    {
        return &_mutex;
    }
private:
    pthread_mutex_t _mutex;
};

class Condition:public MutexLock
{
public:
    Condition()
    {
        cout << "Cond Init " << endl;
        pthread_cond_init(&_cond,NULL);
    }
    ~Condition()
    {
        cout << "Cond Destory " << endl;
        pthread_cond_destroy(&_cond);
    }
    void wait()
    {
        pthread_cond_wait(&_cond,getMutex());
    }
    void notify()
    {
        pthread_cond_signal(&_cond);
    }
    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
    }
private:
    pthread_cond_t _cond;
};

void * comuse (void * p)
{
    Condition *pmc = (Condition*)p;
    while(1)
    {
    pmc->lock();
    if(num == 0)
    {
        cout << "Consumer : num == 0 , I will sleep" <<endl;
        pmc->wait();
    }
    cout << "Consumer : I will eat..." << endl;
    num--;
    cout <<"Consumer : Eat over now   num = " << num <<endl;
    pmc->unlock();
    sleep(1);
    }
    return NULL;
}



int main()
{
    Condition mc;
    pthread_t pt;
    pthread_create(&pt,NULL,comuse,(void*)&mc);
    while(1)
    {
    mc.lock();
    if(num < 10)
    {
    cout << "Productor : I will create..." << endl;
    num++;
    cout <<"Productor : create over now   num = " << num <<endl;
    }
    mc.unlock();
    mc.notify();
    sleep(2);
    }
    return 0;
}

