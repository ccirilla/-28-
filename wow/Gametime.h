#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>


class GameTime
{
public:
    static GameTime * getInstance();

    static void init();

    static void destroy();

    void showTime() const;

    void clear(int max);

    int updateTime();
private:
    GameTime() {}  

private:
    static GameTime * _pInstance;
    static pthread_once_t _once;
    int _time;
    int _max;

};


#endif




