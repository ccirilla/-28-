#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

class Warrior
{
public:
    Warrior(int number,int hp)
        : _number(number)
          , _hp(hp)
    {}
    int getNumber() {  return _number;  }
    int getHp() {  return _hp; }
    virtual ~Warrior(){}
private:
    int _number;
    int _hp;
};

class Dragon
:public Warrior
{
public:
    Dragon(int number,int rest)
        : Warrior(number,price)
          , _weapon(number%3)
          , _morale(double(rest)/price)
    {
        ++num;
    }
    static int getPrice() {return price;}
    static void setPrice(int p) { price = p;}
    static int getNum() {  return num;  }
    void print(int time,const char *color,int sum)
    {
        cout<<setfill('0');
        cout << setw(3) << time << " "<<color <<" dragon " << getNumber()
            << " born with strength " << getHp() << "," << sum <<" dragon in "
            << color << " headquarter" << endl;
        if(_weapon == 0)
            cout << "It has a sword and it's morale is ";
        else if(_weapon == 1)
            cout << "It has a bomb and it's morale is " ;
        else
            cout << "It has a arrow and it's morale is ";
        printf("%.2lf\n",(_morale+0.005));
    }
private:
    int _weapon;
    double _morale;
    static int num;
    static int price;
};

class Ninja
:public Warrior
{
public:
    Ninja(int number)
        : Warrior(number,price)
          , _weapon1(number%3)
          , _weapon2((number+1)%3)
    {
        ++num;
    }
    static int getPrice() {return price;}
    static int getNum() {  return num;  }
    static void setPrice(int p) { price = p;}
    void print(int time,const char *color,int sum)
    {
        cout<<setfill('0');
        cout << setw(3) << time << " "<<color <<" ninja " << getNumber()
            << " born with strength " << getHp() << "," << sum <<" ninja in "
            << color << " headquarter" << endl;
        if(_weapon1 == 0)
            cout << "It has a sword and a bomb" << endl;
        else if(_weapon1 == 1)
            cout << "It has a bomb and a arrow" << endl;
        else
            cout << "It has a arrow and a sword" << endl;
    }
private:
    int _weapon1;
    int _weapon2;
    static int num;
    static int price;
};

class Iceman
:public Warrior
{
public:
    Iceman(int number)
        : Warrior(number,price)
          , _weapon(number%3)
    {
        ++num;
    }
    static int getPrice() {return price;}
    static int getNum() {  return num;  }
    static void setPrice(int p) { price = p;}
    void print(int time,const char *color,int sum)
    {
        cout<<setfill('0');
        cout << setw(3) << time << " "<<color <<" iceman " << getNumber()
            << " born with strength " << getHp() << "," << sum <<" iceman in "
            << color << " headquarter" << endl;
        if(_weapon == 0)
            cout << "It has a sword" << endl;
        else if(_weapon == 1)
            cout << "It has a bomb" << endl;
        else
            cout << "It has a arrow" << endl;
    }
private:
    int _weapon;
    static int num;
    static int price;
};

class Lion
:public Warrior
{
public:
    Lion(int number,int rest)
        : Warrior(number,price)
          , _loyal(rest)
    {
        ++num;
    }
    static int getPrice() {return price;}
    static int getNum() {  return num;  }
    static void setPrice(int p) { price = p;}
    void print(int time,const char *color,int sum)
    {
        cout<<setfill('0');
        cout << setw(3) << time << " "<<color <<" lion " << getNumber()
            << " born with strength " << getHp() << "," << sum <<" lion in "
            << color << " headquarter" << endl;
        cout << "It's loyalty is " << _loyal<< endl;
    }
private:
    int _loyal;
    static int num;
    static int price;
};

class Wolf
:public Warrior
{
public:
    Wolf(int number)
        : Warrior(number,price)
    {
        ++num;
    }
    static int getPrice() {return price;}
    static int getNum() {  return num;  }
    static void setPrice(int p) { price = p;}
    void print(int time,const char *color,int sum)
    {
        cout<<setfill('0');
        cout << setw(3) << time << " "<<color <<" wolf " << getNumber()
            << " born with strength " << getHp() << "," << sum <<" wolf in "
            << color << " headquarter" << endl;
    }
private:
    static int num;
    static int price;
};

class Red
{
public:
    Red(int ret)
        :_ret(ret)
    {}
    bool createWarrior(int time);
private:
    int _number = 1;
    int _pos = 0;
    int _ret;
    int _sum[5] = {0};
    vector<Warrior*> _myWar;
};

class Blue
{
public:
    Blue(int ret)
        :_ret(ret)
    {}
    bool createWarrior(int time);
private:
    int _number = 1;
    int _pos = 0;
    int _ret;
    int _sum[5] = {0};
    vector<Warrior*> _myWar;
};

bool Red::createWarrior(int time)
{
    int i = 0;
    bool flag = false;
    while(1)
    {
        switch(_pos)
        {
        case 0:
            if(_ret >= Iceman::getPrice())
            {
                ++_sum[0];
                _ret -= Iceman::getPrice();
                flag = true;
                Iceman * ice = new Iceman(_number);
                _myWar.push_back(ice);
                ice->print(time,"red",_sum[0]);
                ++_number;
            }
            break;
        case 1:
            if(_ret >= Lion::getPrice())
            {
                ++_sum[1];
                _ret -= Lion::getPrice();
                flag = true;
                Lion * plion = new Lion(_number,_ret);
                _myWar.push_back(plion);
                plion->print(time,"red",_sum[1]);
                ++_number;
            }
            break;
        case 2:
            if(_ret >= Wolf::getPrice())
            {
                ++_sum[2];
                _ret -= Wolf::getPrice();
                flag = true;
                Wolf * pwolf = new Wolf(_number);
                _myWar.push_back(pwolf);
                pwolf->print(time,"red",_sum[2]);
                ++_number;
            }
            break;
        case 3:
            if(_ret >= Ninja::getPrice())
            {
                ++_sum[3];
                _ret -= Ninja::getPrice();
                flag = true;
                Ninja * pninja = new Ninja(_number);
                _myWar.push_back(pninja);
                pninja->print(time,"red",_sum[3]);
                ++_number;
            }
            break;
        case 4:
            if(_ret >= Dragon::getPrice())
            {
                ++_sum[4];
                _ret -= Dragon::getPrice();
                flag = true;
                Dragon * pdragon = new Dragon(_number,_ret);
                _myWar.push_back(pdragon);
                pdragon->print(time,"red",_sum[4]);
                ++_number;
            }
            break;

        }
        _pos = (_pos+1)%5;
        if(flag == true)
            break;
        ++i;
        if( i == 5 )
            break;
    }
    if( i == 5 )
        return false;
    else
        return true;
}

bool Blue::createWarrior(int time)
{
    int i = 0;
    bool flag = false;
    while(1)
    {
        switch(_pos)
        {
        case 3:
            if(_ret >= Iceman::getPrice())
            {
                ++_sum[3];
                _ret -= Iceman::getPrice();
                flag = true;
                Iceman * ice = new Iceman(_number);
                _myWar.push_back(ice);
                ice->print(time,"blue",_sum[3]);
                ++_number;
            }
            break;
        case 0:
            if(_ret >= Lion::getPrice())
            {
                ++_sum[0];
                _ret -= Lion::getPrice();
                flag = true;
                Lion * plion = new Lion(_number,_ret);
                _myWar.push_back(plion);
                plion->print(time,"blue",_sum[0]);
                ++_number;
            }
            break;
        case 4:
            if(_ret >= Wolf::getPrice())
            {
                ++_sum[4];
                _ret -= Wolf::getPrice();
                flag = true;
                Wolf * pwolf = new Wolf(_number);
                _myWar.push_back(pwolf);
                pwolf->print(time,"blue",_sum[4]);
                ++_number;
            }
            break;
        case 2:
            if(_ret >= Ninja::getPrice())
            {
                ++_sum[2];
                _ret -= Ninja::getPrice();
                flag = true;
                Ninja * pninja = new Ninja(_number);
                _myWar.push_back(pninja);
                pninja->print(time,"blue",_sum[2]);
                ++_number;
            }
            break;
        case 1:
            if(_ret >= Dragon::getPrice())
            {
                ++_sum[1];
                _ret -= Dragon::getPrice();
                flag = true;
                Dragon * pdragon = new Dragon(_number,_ret);
                _myWar.push_back(pdragon);
                pdragon->print(time,"blue",_sum[1]);
                ++_number;
            }
            break;

        }
        _pos = (_pos+1)%5;
        if(flag == true)
            break;
        ++i;
        if( i == 5 )
            break;
    }
    if( i == 5 )
        return false;
    else
        return true;
}
int     Dragon::price(3);
int     Ninja::price(4);
int     Iceman::price(5);
int     Lion::price(6);
int     Wolf::price(7);
int     Dragon::num(0);
int     Ninja::num(0);
int     Iceman::num(0);
int     Lion::num(0);
int     Wolf::num(0);


int main()
{
    int ccase;
    int k;
    cin >> ccase;
    cin >> k;
    Red r(k);
    Blue b(k);
    cin >> k;
    Dragon::setPrice(k);
    cin >> k;
    Ninja::setPrice(k);
    cin >> k;
    Iceman::setPrice(k);
    cin >> k;
    Lion::setPrice(k);
    cin >> k;
    Wolf::setPrice(k);
    int i=0;
    bool flagr = true;
    bool flagb = true;
    cout << "Case:" << ccase << endl;
    while(1)
    {
        if(flagr)
        { 
            flagr = r.createWarrior(i);
            if(flagr == false)
            {
                cout << setw(3) << i << " red headquarter stops making warriors" <<endl;
            }
        }
        if(flagb)
        { 
            flagb = b.createWarrior(i);
            if(flagb == false)
            {
                cout << setw(3) << i << " blue headquarter stops making warriors" <<endl;
            }
        }
        if(flagr == false && flagb == false)
            break;
        ++i;
    }
    return 0;
}

