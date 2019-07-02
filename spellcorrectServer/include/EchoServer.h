#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__
#include "TcpConnection.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "MyTask.h"
#include "TimerThread.h"
#include <iostream>
using std::placeholders::_1;
using namespace wd;
using namespace std;
class EchoServer
{
public:
    EchoServer(size_t threadNum,size_t queSize,const string &ip,unsigned short port
               ,int begTime,int valTime,TimerCallback tcb)
    : _threadpool(threadNum,queSize)
    , _server(ip,port)
    , _timeThread(begTime,valTime,move(tcb))
    {
    }
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);
//    void process();
    void start()
    {
        _threadpool.start();
        _timeThread.start();
        _server.setConnectionCallback(std::bind(&EchoServer::onConnection,this,_1));
        _server.setMessageCallback(std::bind(&EchoServer::onMessage,this,_1));
        _server.setCloseCallback(std::bind(&EchoServer::onClose,this,_1));
        _server.start();
    }
private:
    Threadpool _threadpool;
    TcpServer _server;
    TimerThread _timeThread;
};


#endif
