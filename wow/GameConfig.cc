#include "GameConfig.h"
using std::cin;

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
#if 0
int main()
{
    GameConfig::getInstance()->readFromCin();
    cout << "case num  = " << GameConfig::getInstance()->getCaseNum() << endl;
    config *pc = GameConfig::getInstance()->getConfig(1);
    cout << pc->head_hp <<" " << pc->city_num << " " << pc->max_time << endl;
    for(int i=0;i<5;i++)
    {
        cout << pc->warrior_beg_hp[i] << " ";
    }
    cout << endl;
    for(int i=0;i<5;i++)
    {
        cout << pc->warrior_beg_atk[i] << " ";
    }
    cout << endl;
    return 0;
}
#endif

