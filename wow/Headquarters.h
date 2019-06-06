#ifndef __HEADQUARTERS_H__
#define __HEADQUARTERS_H__

#include "Type.h"

class Headquarters
//:public std::enable_shared_from_this<Headquarters>
{
public:
    Headquarters(Color color,int ele,int max)
    :_color(color)
    ,_elements(ele)
    ,_max_city(max)
    {}
    virtual ~Headquarters() {}
    virtual void createWarrior()=0;
    void move(vector<City>&,shared_ptr<Headquarters>);
    void beIntruder (){
        _intruder_flag = true;
    }
    void delIntruder(){
        _intruder_flag = false;
    }
    void addEnemy(WarriorPtr war){
        _enemy.push_back(war);
    }
    bool getIntruder(){
        return _intruder_flag;
    }
    WarriorPtr getEnemy(){
        return _enemy.back();
    }
    int enemyNum(){
        return _enemy.size();
    }
    void gainEle(int ele){
        _elements += ele;
    }
    void delWarrior(WarriorPtr p);
    void getWinEle(int  ele){
        will_add_ele += ele;
    }
    void addWinele(){
        _elements += will_add_ele;
        will_add_ele = 0;
    }
    int getElement(){
        return _elements;
    }
    void awardWarrior(){
        _elements -= 8;
    }
    void print();
protected:
    vector<WarriorType> _warriorCreatingOrder;
    Color _color;
    int _elements;
    int _nextWarriorIndex = 1;
    vector<shared_ptr<Warrior>> _warriors;
    bool _intruder_flag = false;
    vector<shared_ptr<Warrior>> _enemy;
    int will_add_ele = 0;
    int _max_city;
};


class RedHeadquarters
:public Headquarters
,public std::enable_shared_from_this<Headquarters>
{
public:
    RedHeadquarters(int,int);
    void createWarrior();
};

class BlueHeadquarters
:public Headquarters
,public std::enable_shared_from_this<Headquarters>
{
public:
    BlueHeadquarters(int ,int);
    void createWarrior();
};
#endif
