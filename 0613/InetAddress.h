#ifndef __WD_INETADDRESS_H__
#define __WD_INETADDRESS_H__

#include <arpa/inet.h>
#include <string>
using std::string;

namespace wd
{

class InetAddress
{
public:
    InetAddress(unsigned short port);
    InetAddress(const string & ip,unsigned short port);
    InetAddress(const struct sockaddr_in & addr);
    unsigned short port()const;
    string ip()const;
    struct sockaddr_in* getInetAddressPtr() {   return &_addr;  }
private:
    struct sockaddr_in _addr;
};

}
#endif
