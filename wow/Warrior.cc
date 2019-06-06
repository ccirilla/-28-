#include "Warrior.h"
#include "City.h"
#include "Headquarters.h"

int Dragon::_init_hp;
int Dragon::_init_atk;
int Iceman::_init_hp;
int Iceman::_init_atk;
int Lion::_init_hp;
int Lion::_init_atk;
int Wolf::_init_hp;
int Wolf::_init_atk;
int Ninja::_init_hp;
int Ninja::_init_atk;


Warrior::Warrior(Color color,WarriorType type,int id,
                 int hp,int atk,shared_ptr<Headquarters> phead)
    : _color(color)
    , _type(type)
    , _id(id)
    , _hp(hp)
    , _atk(atk)
      , _phead(phead)
{}

Dragon::Dragon(Color color,int id,shared_ptr<Headquarters> phead)
    :Warrior(color,DRAGON_TYPE,id,_init_hp,_init_atk,phead)
{
}

Ninja::Ninja(Color color,int id,shared_ptr<Headquarters> phead)
    :Warrior(color,NINJA_TYPE,id,_init_hp,_init_atk,phead)
{
}

Iceman::Iceman(Color color,int id,shared_ptr<Headquarters> phead)
    :Warrior(color,ICEMAN_TYPE,id,_init_hp,_init_atk,phead)
{
}

Lion::Lion(Color color,int id,shared_ptr<Headquarters> phead)
    :Warrior(color,LION_TYPE,id,_init_hp,_init_atk,phead)
{
}

Wolf::Wolf(Color color,int id,shared_ptr<Headquarters> phead)
    :Warrior(color,WOLF_TYPE,id,_init_hp,_init_atk,phead)
{
}

void Warrior::move(vector<City> & city,shared_ptr<Headquarters> p)
{
    if(_color == RED)
    {
        if(_belong_city_num == int(city.size()))
        {
            if(shared_from_this() == city.back().getPred())
                city.back().getPred().reset();
            _belong_city_num = -1;
            p->beIntruder();
            p->addEnemy(shared_from_this());
        }
        else
        {
        if(_belong_city_num != 0 && shared_from_this() == city[_belong_city_num-1].getPred())
            city[_belong_city_num-1].getPred().reset();
        _belong_city_num++;
        city[_belong_city_num-1].getPred() = shared_from_this();
        }
    }else
    {
        if(_belong_city_num == 1)
        {
            if(shared_from_this() == city.front().getPblue())
                city.front().getPblue().reset();
            _belong_city_num = -1;
            p->beIntruder();
            p->addEnemy(shared_from_this());
        }else if(_belong_city_num == 0)
        {
            _belong_city_num = city.size();
            city[_belong_city_num-1].getPblue() = shared_from_this();
        }else
        {
            if(shared_from_this() == city[_belong_city_num-1].getPblue())
                city[_belong_city_num-1].getPblue().reset();
            _belong_city_num--;
            city[_belong_city_num-1].getPblue() = shared_from_this();
        }
    }
}

void Iceman::move(vector<City> & city,shared_ptr<Headquarters>p)
{
    Warrior::move(city,p);
    _move_sum++;
    if(_move_sum % 2 == 0)
    {
        _atk += 20;
        if(_hp <= 9)
            _hp = 0;
        else
            _hp -= 9;
    }
}

int Warrior::attack(WarriorPtr rhs)
{
    GameTime::getInstance()->showTime();
    WarriorView::showName(shared_from_this());
    cout << "attacked ";
    WarriorView::showName(rhs);
    cout << "in city "<< rhs->getBelong() << " ";
    WarriorView::showAbility(shared_from_this());
    cout << endl;
    if(_atk >= rhs->get_hp())
        return 1;
    else
    {
        rhs->beAttacked(_atk);
        return 0;
    }
}

int Wolf::attack(WarriorPtr rhs)
{
    int ret = Warrior::attack(rhs);
    if( ret == 1 )
    {
        _kill_sum++;
        if(_kill_sum % 2 == 0)
        {
            _atk *= 2;
            _hp *= 2;
        }
    }
    return ret;
}

void Warrior::beKilled(WarriorPtr rhs)
{
    GameTime::getInstance()->showTime();
    WarriorView::showName(shared_from_this());
    cout << "was killed in city "
         << _belong_city_num << endl;
    _phead->delWarrior(shared_from_this());
}

void Lion::beKilled(WarriorPtr rhs)
{
    rhs->getLion(_hp);
    Warrior::beKilled(rhs);
}

void Dragon::cheer()
{
    GameTime::getInstance()->showTime();
    WarriorView::showName(shared_from_this());
    cout << "yelled in city "
         << getBelong() << endl;
}

void Warrior::getWinEle(int ele){
    _phead->getWinEle(ele);
    GameTime::getInstance()->showTime();
    WarriorView::showName(shared_from_this());
    cout << "earned " << ele 
         << " elements for his headquarter" << endl;
}

int Warrior::back_attack(WarriorPtr rhs){
    GameTime::getInstance()->showTime();
    WarriorView::showName(shared_from_this());
    cout << "fought back against ";
    WarriorView::showName(rhs);
    cout << "in city "<< rhs->getBelong() << endl;
    if(_atk/2 >= rhs->get_hp())
        return 1;
    else
    {
        rhs->beAttacked(_atk/2);
        return 0;
    }

}

void Warrior::getAward()
{
    if(_phead->getElement() >= 8)
    {
        _phead->awardWarrior();
        _hp += 8;
    }
}
