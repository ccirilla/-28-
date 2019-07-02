#include "../include/EchoServer.h"

void EchoServer::onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl << endl;
    conn->send("welcome to server.");
}

void EchoServer::onClose(const wd::TcpConnectionPtr & conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl << endl;
}

void EchoServer::onMessage(const wd::TcpConnectionPtr & conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    if(msg.back()=='\n'){
        msg.resize(msg.size()-1);
    }
    MyTask task(msg,conn);
    cout << ">> receive msg from client: " << msg << endl;
    _threadpool.addTask(std::bind(&MyTask::process,task));
}


