#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__


#include <functional>
using namespace std;

namespace wd
{

using TimerCallback = function<void()>;

class Timer
{
public:
    Timer(int initTime, int intervalTime,TimerCallback && cb);
    ~Timer();
    void start();
    void stop();
    void setTimer(int initTime, int intervalTime);
private:
    int createTimerfd();
    void  handleRead();
private:
    int _fd;
    int _initalTime;
    int _intervalTime;
    bool _isStarted;
    TimerCallback _cb;
};

}
#endif
