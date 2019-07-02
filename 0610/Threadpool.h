#ifndef __QQ__
#define __QQ__
#include "TaskQue.h"
#include "Thread.h"
#include <vector>
#include <memory>
using namespace std;

class Threadpool
{
public:
    friend class WorkerThread;
    Threadpool(int tnum,int qnum)
    : _threadNum(tnum)
    , _queSize(qnum)
    , _que(_queSize)
    {   _threads.reserve(_threadNum);   }
    ~Threadpool() {     cout << "~Threadpool()"<<endl;  }
    void start();
    void stop();
    void addTask(Task*);
private:
    Task* getTask();
    void ThreadFunc();
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQue _que;
    bool _isExit = false;
};

#endif
