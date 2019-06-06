#ifndef __WARRCRAFTWORLD_H__
#define __WARRCRAFTWORLD_H__

#include "City.h"
#include "Gametime.h"
#include "GameConfig.h"
#include "Type.h"
#include "Warrior.h"
#include "Headquarters.h"
#include <iostream>
using namespace std;


class WarcraftWorld
{
public:
    WarcraftWorld(config*);
    void gameBegin();

private:
    void init(config*);
    bool printMove();
    void product();
    void earnEle();
    void beginWar();
    void print();
//    void createWarrior(shared_ptr<Headquarters>);
private:
    shared_ptr<Headquarters> _red;
    shared_ptr<Headquarters> _blue;
    vector<City> _city;
};

#endif


