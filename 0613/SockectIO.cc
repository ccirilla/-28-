#include "SockectIO.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

SockectIO::SockectIO(int fd)
: _fd(fd)
{}

int SockectIO::readn(char *buf,int len)
{
    int left = len;
    int ret;
    char *p = buf;
    while(left > 0)
    {
        ret = ::read(_fd,p,left);
        if(ret == -1 && errno == EINTR)
            continue;
        else if(ret == -1){
            perror("read");
            return len - left;
        }
        else if(ret == 0)
        {
            return len -left;
        }
        else{
            left -= ret;
            p += ret;
        }
    }
    return len - left;
}

int SockectIO::writen(const char * buf,int len)
{
    const char *p= buf;
    int left = len;
    int ret;
    while(left > 0)
    {
        ret = ::write(_fd,p,left);
        if(ret == -1 && errno == EINTR)
            continue;
        else if(ret == -1){
            perror("write");
            return len - left;
        }
        else{
            p += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SockectIO::recvPeek(char * buff, int len)
{
    int ret;
    do{
        ret = ::recv(_fd,buff,len,MSG_PEEK);
    }while( ret == -1 && errno == EINTR);
    return ret;
}

int SockectIO::readline(char *buf,int maxlen)
{
    int left = maxlen -1;
    int ret;
    int total = 0;
    char *p = buf;
    while(left > 0)
    {
        ret = recvPeek(p,left);
        for(int idx = 0;idx != ret ;idx++)
        {
            if(p[idx] == '\n')
            {
                int sz = idx + 1;
                readn(p,sz);
                total += sz;
                p += sz;
                *p = '\0';
                return total;
            }
        }
        readn(p,ret);
        left -= ret;
        p += ret;
        total += ret;
    }
    *p = '\0';
    return total;
}

}

