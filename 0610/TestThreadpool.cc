#include "Threadpool.h"
#include "Task.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;



class Mytask
:public Task
{
    void process()
    {
        ::srand(::time(NULL));
        int number = ::rand() % 100;
        cout << ">> sub thread " << pthread_self() 
            << " create a number  " << number << endl;
        ::sleep(1);
    }
};


int main()
{
    Threadpool threadpool(4,10);
    threadpool.start();
    //cout << "11111111" << endl;
    unique_ptr<Task> task(new Mytask());
    int cnt = 20;
    while(cnt--) {
        threadpool.addTask(task.get());
        cout << ">> cnt = " << cnt << endl;

    }

    threadpool.stop();

    return 0;
}

