#include "Gametime.h"
#include <iomanip>
using namespace std;

GameTime * GameTime::_pInstance = nullptr;
pthread_once_t GameTime::_once;

GameTime * GameTime::getInstance()
{
    pthread_once(&_once,init);
    return _pInstance;
}

void GameTime::init()
{
    if(!_pInstance)
    {
        _pInstance = new GameTime();
        atexit(destroy);
    }
}

void GameTime::destroy()
{
    delete _pInstance;
}

void GameTime::showTime() const
{
    int h = _time / 60;
    int m = _time % 60;
    cout << setfill('0');
    cout << setw(3) << h << ":" << setw(2) << m << " ";
}

void GameTime::clear(int max)
{
    _time = 0;
    _max = max;
}

int GameTime::updateTime()
{
    _time += 10;
    if(_time >= _max)
        return -1;
    else
        return 0;
}


