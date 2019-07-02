#include "Threadpool.h"
#include "TcpServer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::placeholders::_1;

//wd::Threadpool * gThreadpool = nullptr;

class Task
{
public:
    Task(const string &msg,wd::TcpConnectionPtr conn)
        : _msg(msg)
          , _conn(conn)
    {}
    void process()
    {
        string response = _msg;
        _conn->sendInLoop(response);
    }
private:
    string _msg;
    wd::TcpConnectionPtr _conn;
};

using namespace wd;
class EchoServer
{
public:
    EchoServer(size_t threadNum,size_t queSize,const string &ip,unsigned short port)
    : _threadpool(threadNum,queSize)
    , _server(ip,port)
    {}
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);
    void process();
    void start()
    {
        _threadpool.start();
        _server.setConnectionCallback(std::bind(&EchoServer::onConnection,this,_1));
        _server.setMessageCallback(std::bind(&EchoServer::onMessage,this,_1));
        _server.setCloseCallback(std::bind(&EchoServer::onClose,this,_1));
        _server.start();
    }
private:
    Threadpool _threadpool;
    TcpServer _server;
};
void EchoServer::onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
    conn->send("welcome to server.");
}

void EchoServer::onClose(const wd::TcpConnectionPtr & conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl;
}

void EchoServer::onMessage(const wd::TcpConnectionPtr & conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    ::Task task(msg,conn);
    cout << ">> receive msg from client: " << msg << endl;
    _threadpool.addTask(std::bind(&::Task::process,task));
}




#if 0
int main()
{
    wd::Threadpool threadpool(4, 10); 
    threadpool.start();
    gThreadpool = &threadpool;
    wd::TcpServer server("0.0.0.0", 8888);
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);
    server.start();
    return 0;
}
#endif

int main()
{
    EchoServer ecoserver(4,10,"0.0.0.0",8888);
    ecoserver.start();
}

