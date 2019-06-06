#include "City.h"
#include "Warrior.h"
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
            if( ret == 1 )
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
            if( ret == 1 )
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


