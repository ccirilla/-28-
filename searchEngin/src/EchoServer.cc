#include "../include/EchoServer.h"

void EchoServer::onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl << endl;
    //conn->send("welcome to server.");
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
    if(msg.back() == '\n')
        msg.back() = 0;
    cout << ">> receive msg from client: " << msg << endl;
    _threadpool.addTask(std::bind(&EchoServer::doTaskThread,this,conn,msg));
}
/*
void EchoServer::doTaskThread(const TcpConnectionPtr& conn,const string& msg)
{
    string ret = _dict.doQuery(msg);
    int lenth = ret.size();
    ret = to_string(lenth) + "\n" + ret;
    conn->sendInLoop(ret);
}
*/
void EchoServer::doTaskThread(const TcpConnectionPtr & conn, const string & msg)
{
	string ret = _dict.doQuery(msg);

	int sz = ret.size();
	printf("result's size:%d\n",sz); 
	//printf("%s\n\n", ret.c_str());
	//string slength((const char *)&sz, 4);

	string message(to_string(sz));
	message.append("\n").append(ret);
	//printf("message's size:%d\n",message.size()); 
	//conn->sendInLoop(slength);
	
	conn->sendInLoop(message);
}

int main()
{
    Configuration::getInstance("../conf/myconf.conf");
    map<string,string> conf = Configuration::getInstance()->getConfigMap();
    EchoServer ecoserver(stoi(conf["threadNum"]),
                         stoi(conf["queSize"]),
                         conf["ip"],
                         stoi(conf["port"]));
    ecoserver.start();
}

