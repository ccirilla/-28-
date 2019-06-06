#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
using std::map;
using std::vector;

struct config
{
    int head_hp;
    int city_num;
    int max_time;
    map<int,int> warrior_beg_hp;
    map<int,int> warrior_beg_atk;
};

class GameConfig
{
public:
    static GameConfig* getInstance();
    static void destroy();
    void readFromCin();
    int getCaseNum();
    config* getConfig(int i);
private:
    GameConfig() {}
    ~GameConfig() {}
private:
    static GameConfig* _pInstance;
    int _case_num;
    vector<config> _data;
};

#endif
