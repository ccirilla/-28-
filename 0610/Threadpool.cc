#include "Threadpool.h"
#include "TaskQue.h"
#include "WorkerThread.h"
#include "Task.h"

void Threadpool::start()
{
    for(size_t idx = 0 ;idx < _threadNum; ++idx)
    {
        unique_ptr<Thread> temp(new WorkerThread(*this));
        _threads.push_back(move(temp));
    }
    for(auto & thread : _threads)
        thread->start();
    //cout << "11111111111" <<endl;
}

void Threadpool::stop()
{
    if(!_isExit)
    {
        while(!_que.empty())
        {
            sleep(1);
        }
        _isExit = true;
        for(size_t idx=0;idx!=_threadNum;idx++)
            addTask(nullptr);
        for(auto & thread : _threads)
            thread->join();
    }
}

void Threadpool::addTask(Task * task)
{
    _que.push(task);
}

Task * Threadpool::getTask()
{
    return _que.pop();
}

void Threadpool::ThreadFunc()
{
    while(!_isExit)
    {
        Task *task = getTask();
        if(task)
            task->process();
    }
}
