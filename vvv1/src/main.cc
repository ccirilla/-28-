#include "../include/EchoServer.h"
#include "../include/Mydict.h"
#include "../include/Configuration.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <functional>
using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::placeholders::_1;


using namespace wd;
#if 0
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
//    void process();
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
    MyTask task(msg,conn);
    cout << ">> receive msg from client: " << msg << endl;
    _threadpool.addTask(std::bind(&MyTask::process,task));
}

#endif


int main()
{
    Configuration::getInstance("../conf/configure.txt");
    Mydict::getInstance()->read();
    map<string,string> conf = Configuration::getInstance()->getConfigMap();
    EchoServer ecoserver(stoi(conf["threadNum"]),
                         stoi(conf["queSize"]),
                         conf["ip"],
                         stoi(conf["port"]));
    ecoserver.start();
}

