#pragma once
#include "Thread.h"
class Threadpool;

class WorkerThread
:public Thread
{
public:
    WorkerThread(Threadpool &);
    void run() override;
private:
    Threadpool &_thread_pool;
};

