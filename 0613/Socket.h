#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

namespace wd
{

class Socket
{
public:
    Socket();
    explicit
    Socket(int fd);
    ~Socket();
    int fd()const;
    void shutdownWrite();
private:
    int _fd;
};

}
#endif
