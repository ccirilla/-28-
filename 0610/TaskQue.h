#ifndef __HH__
#define __HH__
#include <iostream>
#include <queue>

class Task;

using namespace std;


class Noncopyable
{
protected:
    Noncopyable(){}
    Noncopyable(const Noncopyable &rhs) = delete;
    Noncopyable & operator = (const Noncopyable &rhs) = delete ;
};

class MutexLock
:Noncopyable
{
public:
    MutexLock(){
        pthread_mutex_init(&_mutex,nullptr);
    }
    void lock(){
        pthread_mutex_lock(&_mutex);
        _isLocking = true;
    }
    void unlock(){
        pthread_mutex_unlock(&_mutex);
        _isLocking = false;
    }
    bool isLocking()const{
        return _isLocking;
    }
    pthread_mutex_t * getMutexLockPtr(){
        return &_mutex;
    }
    ~MutexLock(){
        pthread_mutex_destroy(&_mutex);
    }
private:
    pthread_mutex_t _mutex;
    bool _isLocking = false;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
        :_mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard(){
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};

class Condition
:Noncopyable
{
public:
    Condition(MutexLock & mutex)
        :_mutex(mutex)
    {
        pthread_cond_init(&_cond,nullptr);
    }
    ~Condition(){
        pthread_cond_destroy(&_cond);
    }
    void wait(){
        pthread_cond_wait(&_cond,_mutex.getMutexLockPtr());
    }
    void notify(){
        pthread_cond_signal(&_cond);
    }
    void notifyAll(){
        pthread_cond_broadcast(&_cond);
    }
private:
    MutexLock & _mutex;
    pthread_cond_t _cond;
};


class TaskQue
{
public:
    TaskQue(int size= 10);
    ~TaskQue() {}
    void push(Task*);
    Task* pop();
    bool full(){
        return _que.size() == _queSize;
    }
    bool empty(){
        return _que.empty();
    }
private:
    size_t _queSize;
    queue<Task*> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

#endif
