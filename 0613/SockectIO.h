#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{

class SockectIO
{
public:
    SockectIO(int fd);
    int readn(char *buf,int len);
    int writen(const char *buf,int len);
    int readline(char *buf,int maxlen);
private:
    int recvPeek(char *buf,int len);
private:
    int _fd;
};

}
#endif
