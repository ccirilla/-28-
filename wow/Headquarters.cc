#include "Headquarters.h"
#include "Warrior.h"
#include <algorithm>

#if 0
Headquarters::Headquarters(Color color,int ele,int max)
:_color(color)
,_elements(ele)
,_max_city(max)
{}
#endif

RedHeadquarters::RedHeadquarters(int hp,int max)
:Headquarters(RED,hp,max)
{
    _warriorCreatingOrder = { ICEMAN_TYPE,LION_TYPE,
        WOLF_TYPE,NINJA_TYPE,DRAGON_TYPE };
}

BlueHeadquarters::BlueHeadquarters(int hp,int max)
:Headquarters(BLUE,hp,max)
{
    _warriorCreatingOrder = { LION_TYPE,DRAGON_TYPE
        ,NINJA_TYPE,ICEMAN_TYPE,WOLF_TYPE };
}

void RedHeadquarters::createWarrior()
{
    WarriorType war = _warriorCreatingOrder[(_nextWarriorIndex - 1) % 5];
    switch(war)
    {
    case DRAGON_TYPE:
        if(_elements < Dragon::getHp())
            return ;
        _elements -= Dragon::getHp();
        _warriors.emplace_back(new Dragon(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case NINJA_TYPE:
        if(_elements < Ninja::getHp())
            return ;
        _elements -= Ninja::getHp();
        _warriors.emplace_back(new Ninja(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case ICEMAN_TYPE:
        if(_elements < Iceman::getHp())
            return ;
        _elements -= Iceman::getHp();
        _warriors.emplace_back(new Iceman(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case LION_TYPE:
        if(_elements < Lion::getHp())
            return ;
        _elements -= Lion::getHp();
        _warriors.emplace_back(new Lion(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case WOLF_TYPE:
        if(_elements < Wolf::getHp())
            return ;
        _elements -= Wolf::getHp();
        _warriors.emplace_back(new Wolf(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    }
    ++ _nextWarriorIndex;
    GameTime::getInstance()->showTime();
    WarriorView::showName(_warriors.back());
    cout << "born" << endl;
}

void BlueHeadquarters::createWarrior()
{
    WarriorType war = _warriorCreatingOrder[(_nextWarriorIndex - 1) % 5];
    switch(war)
    {
    case DRAGON_TYPE:
        if(_elements < Dragon::getHp())
            return ;
        _elements -= Dragon::getHp();
        _warriors.emplace_back(new Dragon(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case NINJA_TYPE:
        if(_elements < Ninja::getHp())
            return ;
        _elements -= Ninja::getHp();
        _warriors.emplace_back(new Ninja(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case ICEMAN_TYPE:
        if(_elements < Iceman::getHp())
            return ;
        _elements -= Iceman::getHp();
        _warriors.emplace_back(new Iceman(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case LION_TYPE:
        if(_elements < Lion::getHp())
            return ;
        _elements -= Lion::getHp();
        _warriors.emplace_back(new Lion(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    case WOLF_TYPE:
        if(_elements < Wolf::getHp())
            return ;
        _elements -= Wolf::getHp();
        _warriors.emplace_back(new Wolf(_color,_nextWarriorIndex,
                                          shared_from_this()));
        break;
    }
    ++ _nextWarriorIndex;
    GameTime::getInstance()->showTime();
    WarriorView::showName(_warriors.back());
    cout << "born" << endl;
}
void Headquarters::move(vector<City>& city,shared_ptr<Headquarters> p)
{
    for(auto &s : _warriors)
        if(s->getBelong() != -1)
            s->move(city,p);
}

void Headquarters::delWarrior(WarriorPtr p){
    auto it = find(_warriors.begin(),_warriors.end(),p);
    _warriors.erase(it);
}

void Headquarters::print()
{
    GameTime::getInstance()->showTime();
    cout << _elements << " elements in "
         << toString(_color) << " headquarter" << endl;
}
