#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__
#include "Socket.h"
#include "InetAddress.h"
#include "SockectIO.h"
#include "Noncopyable.h"

#include <string>
#include <memory>
#include <functional>
using std::string;
using std::function;

namespace wd
{

class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

class TcpConnection
    :Noncopyable
     ,public std::enable_shared_from_this<TcpConnection>
    {
    public:
        TcpConnection(int fd);
        ~TcpConnection();
        string receive();
        void send(const string &msg);
        string toString()const;
        void shutdown();

        void setConnectionCallback(const TcpConnectionCallback & cb);
        void setMessageCallback(const TcpConnectionCallback & cb);
        void setCloseCallback(const TcpConnectionCallback & cb);

        void handleConnectionCallback();
        void handleMessageCallback();
        void handleCloseCallback();
    private:
        InetAddress getLocalAddr();
        InetAddress getPeerAddr();
    private:
        Socket _sock;
        SockectIO _socketIo;
        InetAddress _localAddr;
        InetAddress _peerAddr;
        bool _isShutdwonWrite;
        TcpConnectionCallback _onConnection;
        TcpConnectionCallback _onMessage;
        TcpConnectionCallback _onClose;
    };
}

#endif
