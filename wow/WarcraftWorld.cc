#include "WarcraftWorld.h"
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

