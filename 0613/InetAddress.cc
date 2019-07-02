#include "InetAddress.h"
#include <string.h>

namespace wd
{

InetAddress::InetAddress(unsigned short port)
{
    bzero(&_addr,sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const string & ip,unsigned short port)
{
    bzero(&_addr,sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
:_addr(addr)
{}

unsigned short InetAddress::port()const
{
    return ntohs(_addr.sin_port);
}

string InetAddress::ip()const
{
    return string(inet_ntoa(_addr.sin_addr));
}

}
