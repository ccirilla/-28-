#ifndef __CITY_H__
#define __CITY_H__

#include "Type.h"
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

#endif
