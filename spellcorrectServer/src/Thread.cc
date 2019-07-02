 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:51:40
 ///
 

#include "../include/Thread.h"
#include <iostream>
using std::cout;
using std::endl;

__thread int threadID;


namespace wd
{

Thread::Thread(ThreadCallback && cb,int id)
: _pthid(0)
, _cb(std::move(cb))
, _isRunning(false)
, _threadID(id)
{
	cout << "Thread(): "  << _threadID << endl;
}

void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);	
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
    threadID = pthread->_threadID;
//    cout << pthread_self() << ": " << threadID << endl;
	if(pthread)
		pthread->_cb();

	return nullptr;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);	
	}
	cout << "~Thread()" << endl;
}

}//end of namespace wd
