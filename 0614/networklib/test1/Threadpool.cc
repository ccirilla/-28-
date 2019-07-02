#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd 
{

Threadpool::Threadpool(size_t threadNum,size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _que(_queSize)
, _isExit(false)
{    _threads.resize(_threadNum);    }

void Threadpool::start()
{
    for(size_t idx = 0; idx != _threadNum; idx++ )
    {
        unique_ptr<Thread> thread(
                new Thread(std::bind(&Threadpool::threadFunc,this)));
        _threads.push_back(std::move(thread));
    }
    for(auto & thread : _threads){
        thread->start();
    }
}

void Threadpool::stop()
{
    if(!_isExit)
    {
        while(!_que.empty()){
            sleep(1);
        }
        _isExit = true;
        _que.wakeup();
        for(auto & thread : _threads){
            thread->join();
        }
    }
}

void Threadpool::addTask(Task && task)
{
    _que.push(task);
}

Task Threadpool::getTask()
{
    return _que.pop();
}

void Threadpool::threadFunc()
{
    while(!_isExit){
        Task task = getTask();
        if(task){
            task();
        }
    }
}

}
