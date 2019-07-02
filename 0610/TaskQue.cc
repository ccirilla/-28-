#include "TaskQue.h"

TaskQue::TaskQue(int size)
: _queSize(size)
, _notFull(_mutex)
, _notEmpty(_mutex)
{}

void TaskQue::push(Task* sfd)
{
    _mutex.lock();
    if(full())
        _notFull.wait();
    _que.push(sfd);
    _mutex.unlock();
    _notEmpty.notify();
}

Task* TaskQue::pop()
{
    _mutex.lock();
    if(empty())
        _notEmpty.wait();
    Task* temp = _que.front();
    _que.pop();
    _mutex.unlock();
    _notFull.notify();
    return temp;
}


