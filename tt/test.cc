#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iomanip>
#include <algorithm>
using namespace std;

class Headquarters;
class City;

enum Color { 
    MID=0,
    RED, 
    BLUE 

};

enum WarriorType { 
    DRAGON_TYPE, 
    NINJA_TYPE, 
    ICEMAN_TYPE, 
    LION_TYPE, 
    WOLF_TYPE 

};

enum WeaponType{ 
    SWORD_TYPE, 
    BOMB_TYPE, 
    ARROW_TYPE 

};

using std::string;
inline string toString(Color color) 
{
    return (color == RED) ? string("red"): string("blue");

}

inline string toString(WarriorType type)
{
    switch(type) {
    case DRAGON_TYPE: return "dragon";
    case NINJA_TYPE:  return "ninja";
    case ICEMAN_TYPE: return "iceman";
    case LION_TYPE:   return "lion";
    case WOLF_TYPE:   return "wolf";
    default:
                      return string();

    }


}

inline string toString(WeaponType type) 
{
    switch(type) {
    case SWORD_TYPE: return "sword";
    case BOMB_TYPE:  return "bomb";
    case ARROW_TYPE: return "arrow";
    default:
                     return string();


    }


}

class Warrior;
class WarriorView;
class City;
class Weapon;
class WeaponView;

using std::shared_ptr;

using WarriorPtr = shared_ptr<Warrior>;
using WarriorViewPtr = shared_ptr<WarriorView>;
using WeaponPtr = shared_ptr<Weapon>;
using WeaponViewPtr = shared_ptr<WeaponView>;

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

class GameTime
{
public:
    static GameTime * getInstance();

    static void destroy();

    void showTime() const;

    void clear(int max);

    int updateTime();
private:
    GameTime() {}  

private:
    static GameTime * _pInstance;
    int _time;
    int _max;
};

class Warrior
:public std::enable_shared_from_this<Warrior>
{
public:

    Warrior(Color color,WarriorType type,int id,int hp,
            int atk,shared_ptr<Headquarters> phead);
    virtual ~Warrior() {}

    virtual void move(vector<City> &,shared_ptr<Headquarters>);

    virtual int attack(WarriorPtr rhs);

    virtual int back_attack(WarriorPtr rhs);

    int get_hp(){
        return _hp;

    }

    int get_atk(){
        return _atk;

    }

    Color get_color(){
        return _color;

    }

    WarriorType get_type(){
        return _type;

    }

    int get_id(){
        return _id;

    }
    int getBelong(){
        return _belong_city_num;

    }
    void gain(int ele);
    void beAttacked(int atk){
        _hp -= atk;

    }
    virtual void beKilled(WarriorPtr rhs);
    void getLion(int hp){
        _hp += hp;

    }
    virtual void cheer(){};
    void getWinEle(int);
    void getAward();
protected:
    int _hp;
    int _atk;
private:
    Color _color;
    WarriorType _type;
    int _id;
    int _belong_city_num = 0;
    shared_ptr<Headquarters> _phead;

};

class Dragon
: public Warrior
{
public:
    Dragon(Color color,int id,shared_ptr<Headquarters> phead);
    static int  getHp(){
        return _init_hp;

    }
    static void  setHp(int hp){
        _init_hp = hp;

    }
    static int  getAtk(){
        return _init_atk;

    }
    static void  setAtk(int atk){
        _init_atk = atk;

    }
    void cheer();
private:
    static int _init_hp;
    static int _init_atk;

};

class Ninja
: public Warrior
{
public:
    Ninja(Color color,int id,shared_ptr<Headquarters> phead);
    static int  getHp(){
        return _init_hp;

    }
    static void  setHp(int hp){
        _init_hp = hp;

    }
    static int  getAtk(){
        return _init_atk;

    }
    static void  setAtk(int atk){
        _init_atk = atk;

    }
    int back_attack(WarriorPtr rhs){
        return 0;
    }
private:
    static int _init_hp;
    static int _init_atk;

};

class Iceman
: public Warrior
{
public:
    Iceman(Color color,int id,shared_ptr<Headquarters> phead);
    static int  getHp(){
        return _init_hp;

    }
    static void  setHp(int hp){
        _init_hp = hp;

    }
    static int  getAtk(){
        return _init_atk;

    }
    static void  setAtk(int atk){
        _init_atk = atk;

    }
    void move(vector<City> &,shared_ptr<Headquarters>);
private:
    static int _init_hp;
    static int _init_atk;
    int _move_sum = 0;

};

class Lion
: public Warrior
{
public:
    Lion(Color color,int id,shared_ptr<Headquarters> phead);
    static int  getHp(){
        return _init_hp;

    }
    static void  setHp(int hp){
        _init_hp = hp;

    }
    static int  getAtk(){
        return _init_atk;

    }
    static void  setAtk(int atk){
        _init_atk = atk;

    }
    void beKilled(WarriorPtr rhs);
private:
    static int _init_hp;
    static int _init_atk;

};

class Wolf
: public Warrior
{
public:
    Wolf(Color color,int id,shared_ptr<Headquarters> phead);
    static int  getHp(){
        return _init_hp;

    }
    static void  setHp(int hp){
        _init_hp = hp;

    }
    static int  getAtk(){
        return _init_atk;

    }
    static void  setAtk(int atk){
        _init_atk = atk;

    }
    int attack(WarriorPtr rhs);
private:
    static int _init_hp;
    static int _init_atk;
    int _kill_sum = 0;

};

class WarriorView
{
public:
    static void showName(shared_ptr<Warrior> p)
    {
        std::cout << toString(p->get_color()) << " "
            << toString(p->get_type()) << " "
            << p->get_id() << " ";

    }
    static void showAbility(shared_ptr<Warrior> p)
    {
        std::cout << "with " << p->get_hp() << " elements and force "
            << p->get_atk();
    }
};

class City
{
public:
    City(int);
    ~City() {}
    WarriorPtr & getPred(){
        return _red_warrior;

    }
    WarriorPtr & getPblue(){
        return _blue_warrior;

    }
    int getNum(){
        return _num;

    }
    void product(){
        _element += 10;

    }
    void earnEle();
    void beginWar();
    void raiseFlg(const string & str);
    void award(Color color);
private:
    int _num;
    int _element = 0;
    shared_ptr<Warrior> _red_warrior;
    shared_ptr<Warrior> _blue_warrior;
    Color _will_award = MID;
    Color _last_win = MID;
    Color _flag = MID;

};

class Headquarters
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
private:
    shared_ptr<Headquarters> _red;
    shared_ptr<Headquarters> _blue;
    vector<City> _city;

};

City::City(int num)
    :_num(num)
{}

void City::earnEle()
{
    if(_red_warrior && !_blue_warrior)
    {
        _red_warrior->gain(_element);
        GameTime::getInstance()->showTime();
        WarriorView::showName(_red_warrior);
        cout << "earned " << _element 
            << " elements for his headquarter" <<endl;
        _element = 0;

    }else if(_blue_warrior && !_red_warrior)
    {
        _blue_warrior->gain(_element);
        GameTime::getInstance()->showTime();
        WarriorView::showName(_blue_warrior);
        cout << "earned " << _element 
            << " elements for his headquarter" <<endl;
        _element = 0;

    }

}

void City::raiseFlg(const string & str)
{
    GameTime::getInstance()->showTime();
    cout << str << _num << endl;

}

void City::beginWar()
{
    if(_red_warrior && _blue_warrior)
    {
        if(_flag == RED || (_flag == MID && _num % 2 == 1))
        {
            int ret = _red_warrior->attack(_blue_warrior);
            if( ret == 1  )
            {
                _blue_warrior->beKilled(_red_warrior);
                _blue_warrior.reset();
                _red_warrior->cheer();
                _will_award = RED;
                _red_warrior->getWinEle(_element);
                _element = 0;
                if(_last_win == RED)
                    raiseFlg("red flag raised in city ");
                _last_win = RED;

            }else
            {
                ret = _blue_warrior->back_attack(_red_warrior);
                if(ret ==  1)
                {
                    _red_warrior->beKilled(_blue_warrior);
                    _red_warrior.reset();
                    _will_award = BLUE;
                    _blue_warrior->getWinEle(_element);
                    _element = 0;
                    if(_last_win == BLUE)
                        raiseFlg("blue flag raised in city ");
                    _last_win = BLUE;

                }else
                {
                    _red_warrior->cheer();
                    _last_win = MID;

                }

            }

        }else
        {
            int ret = _blue_warrior->attack(_red_warrior);
            if( ret == 1  )
            {
                _red_warrior->beKilled(_blue_warrior);
                _red_warrior.reset();
                _blue_warrior->cheer();
                _will_award = BLUE;
                _blue_warrior->getWinEle(_element);
                _element = 0;
                if(_last_win == BLUE)
                    raiseFlg("blue flag raised in city ");
                _last_win = BLUE;

            }else
            {
                ret = _red_warrior->back_attack(_blue_warrior);
                if(ret ==  1)
                {
                    _blue_warrior->beKilled(_red_warrior);
                    _blue_warrior.reset();
                    _will_award = RED;
                    _red_warrior->getWinEle(_element);
                    _element = 0;
                    if(_last_win == RED)
                        raiseFlg("red flag raised in city ");
                    _last_win = RED;

                }else
                {
                    _blue_warrior->cheer();
                    _last_win = MID;

                }

            }

        }        

    }

}

void City::award(Color color)
{
    if(_will_award == color )
    {
        if(color == RED)
        {
            _red_warrior->getAward();

        }else
        {
            _blue_warrior->getAward();

        }
        _will_award = MID;

    }

}

GameConfig* GameConfig::_pInstance = nullptr;
GameConfig* GameConfig::getInstance()
{
    if(!_pInstance)
    {
        _pInstance = new GameConfig();
        atexit(destroy);

    }
    return _pInstance;

}
void GameConfig::destroy()
{
    delete _pInstance;

}
void GameConfig::readFromCin()
{
    cin >> _case_num;
    int value;
    for(int i=0;i<_case_num;i++)
    {
        config temp;
        cin >> temp.head_hp >> temp.city_num >> temp.max_time;
        for(int i=0;i<5;i++)
        {
            cin >> value;
            temp.warrior_beg_hp[i] = value;

        }
        for(int i=0;i<5;i++)
        {
            cin >> value;
            temp.warrior_beg_atk[i] = value;

        }
        _data.push_back(temp);

    }

}
int GameConfig::getCaseNum()
{
    return _case_num;

}
config* GameConfig::getConfig(int i)
{
    return &_data[i-1];

}

GameTime * GameTime::_pInstance = nullptr;

GameTime * GameTime::getInstance()
{
    if(!_pInstance)
    {
        _pInstance = new GameTime();
        atexit(destroy);
    }
    return _pInstance;
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
    : _hp(hp)
    , _atk(atk)
    , _color(color)
    , _type(type)
    , _id(id)
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
    if( ret == 1  )
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

WarcraftWorld::WarcraftWorld(config* conf)
    : _red(new RedHeadquarters(conf->head_hp,conf->city_num))
      , _blue(new BlueHeadquarters(conf->head_hp,conf->city_num))
{
    for(int i=1;i<= conf->city_num;i++)
        _city.emplace_back(i);
    GameTime::getInstance()->clear(conf->max_time);
    init(conf);

}

void WarcraftWorld::init(config *conf)
{
    Dragon::setHp(conf->warrior_beg_hp[0]);
    Dragon::setAtk(conf->warrior_beg_atk[0]);

    Ninja::setHp(conf->warrior_beg_hp[1]);
    Ninja::setAtk(conf->warrior_beg_atk[1]);

    Iceman::setHp(conf->warrior_beg_hp[2]);
    Iceman::setAtk(conf->warrior_beg_atk[2]);

    Lion::setHp(conf->warrior_beg_hp[3]);
    Lion::setAtk(conf->warrior_beg_atk[3]);

    Wolf::setHp(conf->warrior_beg_hp[4]);
    Wolf::setAtk(conf->warrior_beg_atk[4]);

}

bool WarcraftWorld::printMove()
{
    if(_red->getIntruder())
    {
        GameTime::getInstance()->showTime();
        WarriorView::showName(_red->getEnemy());
        cout << "reached red headquarter ";
        WarriorView::showAbility(_red->getEnemy());
        cout << endl;
        _red->delIntruder();

    }
    if(_red->enemyNum() == 2)
    {
        GameTime::getInstance()->showTime();
        cout << "red headquarter was taken" << endl;
        return true;

    }
    for(auto &s : _city)
    {
        if(s.getPred())
        {
            GameTime::getInstance()->showTime();
            WarriorView::showName(s.getPred());
            cout << "marched to city "<<s.getNum() << " ";
            WarriorView::showAbility(s.getPred());
            cout << endl;

        }
        if(s.getPblue())
        {
            GameTime::getInstance()->showTime();
            WarriorView::showName(s.getPblue());
            cout << "marched to city "<<s.getNum() << " ";
            WarriorView::showAbility(s.getPblue());
            cout << endl;

        }

    }
    if(_blue->getIntruder())
    {
        GameTime::getInstance()->showTime();
        WarriorView::showName(_blue->getEnemy());
        cout << "reached blue headquarter ";
        WarriorView::showAbility(_blue->getEnemy());
        cout << endl;
        _blue->delIntruder();

    }
    if(_blue->enemyNum() == 2)
    {
        GameTime::getInstance()->showTime();
        cout << "blue headquarter was taken" << endl;
        return true;

    }else
        return false;

}

void WarcraftWorld::product()
{
    for(auto &s: _city)
        s.product();

}

void WarcraftWorld::earnEle()
{
    for(auto &s: _city)
        s.earnEle();

}

void WarcraftWorld::beginWar()
{
    for(auto &s: _city)
        s.beginWar();
    for(auto &s: _city)
        s.award(BLUE);
    for(auto it = _city.rbegin();it!=_city.rend();++it)
        it->award(RED);
    _red->addWinele();
    _blue->addWinele();

}

void WarcraftWorld::print()
{
    _red->print();
    _blue->print();

}

void WarcraftWorld::gameBegin()
{
    while(1)
    {
        _red->createWarrior();
        _blue->createWarrior();
        if(GameTime::getInstance()->updateTime())
            return;
        _red->move(_city,_blue);
        _blue->move(_city,_red);
        if(printMove())
            return;
        if(GameTime::getInstance()->updateTime())
            return;

        product();
        if(GameTime::getInstance()->updateTime())
            return;

        earnEle();
        if(GameTime::getInstance()->updateTime())
            return;

        beginWar();
        if(GameTime::getInstance()->updateTime())
            return;

        print();
        if(GameTime::getInstance()->updateTime())
            return;

    }

}

void Warrior::gain(int ele)
    {
        _phead->gainEle(ele);
    }



int main()
{
    GameConfig::getInstance()->readFromCin();
    for(int i=1;i<=GameConfig::getInstance()->getCaseNum();i++)
    {
        cout << "Case:" << i << endl;
        WarcraftWorld wow(GameConfig::getInstance()->getConfig(i));
        wow.gameBegin();

    }
    return 0;
}

