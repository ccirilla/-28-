#ifndef _WARRIOR
#define _WARRIOR
#include "Type.h"
#include "Gametime.h"
#include "Headquarters.h"
using std::cout;
using std::endl;
class Warrior
:public std::enable_shared_from_this<Warrior>
{
public:

    Warrior(Color color,WarriorType type,int id,int hp,
            int atk,shared_ptr<Headquarters> phead);
    virtual ~Warrior() {}

    virtual void move(vector<City> &,shared_ptr<Headquarters>);

  //  void showName();

  //  void showAbility();

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
    void gain(int ele){
        _phead->gainEle(ele);
    }
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
//, public std::enable_shared_from_this<Dragon>
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
//, public std::enable_shared_from_this<Ninja>
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
//, public std::enable_shared_from_this<Iceman>
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
//, public std::enable_shared_from_this<Lion>
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
//, public std::enable_shared_from_this<Wolf>
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


#endif
