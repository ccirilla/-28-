#include "TcpServer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

void onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
    conn->send("welcome to server.");
}

void onMessage(const wd::TcpConnectionPtr & conn)
{
    cout << "onMessage...." << endl;
    string msg = conn->receive();
    cout << ">> receive msg from client: " << msg << endl;
    conn->send(msg);
}

void onClose(const wd::TcpConnectionPtr & conn)
{
    cout << "onClose...." << endl;
    cout << conn->toString() << " has closed!" << endl;
}

int main()
{
    wd::TcpServer server("0.0.0.0", 8888);

    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);

    server.start();

    return 0;
}

