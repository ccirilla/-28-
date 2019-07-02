#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__


#include <functional>
using namespace std;

namespace wd
{

using EventfdCallback = function<void()>;

class Eventfd
{
public:
    Eventfd(EventfdCallback && cb);
    ~Eventfd();
    void start();
    void stop();
    void wakeup();
private:
    int createEventfd();
    void  handleRead();
private:
    int _fd;
    bool _isStarted;
    EventfdCallback _cb;
};

}
#endif
