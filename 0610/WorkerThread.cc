#include "WorkerThread.h"
#include "Threadpool.h"


WorkerThread::WorkerThread(Threadpool & threadpool)
:_thread_pool(threadpool)
{}

void WorkerThread::run()
{
    _thread_pool.ThreadFunc();
}


