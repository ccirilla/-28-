#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    {
        _ix = ix;//赋值语句
        _iy = iy;
        cout << "Point(int,int)" << endl;
    }

    void print()
    {
        cout << "(" << _ix
            << "," << _iy 
            << ")" << endl;
    }
    void setX(int ix)
    {   _ix = ix;   }

    void setY(int iy)
    {   _iy = iy;   }
private:
    int _ix;
    int _iy;
};


class Computer
{
public:
    Computer(const char * brand, float price);
    Computer()
    :Computer("",0)
    {}
    Computer(const Computer & rhs)
        : _brand(new char[strlen(rhs._brand) + 1]())//深拷贝
          , _price(rhs._price)
    {
        cout << "Computer(const Computer&)" << endl;
        strcpy(_brand, rhs._brand);
    }

    void print();

    ~Computer()
    {   //做清理工作
        delete [] _brand;
        cout << "~Computer()" << endl;
    }

private:
    char * _brand;
    float _price;//字节对齐, 有4个字节的空间被浪费了
};

Computer::Computer(const char * brand, float price)
    : _brand(new char[strlen(brand) + 1]())
      , _price(price)
{
    cout << "Computer(const char *, float)" << endl;
    strcpy(_brand, brand);

}

void Computer::print()
{
    printf(">> _brand: %p\n", _brand);
    cout << " >> brand: " << _brand << endl
        << " >> price: " << _price << endl;

}

template <typename T>
class Singleton
{
public:
    template <typename... Args>
    static T* getInstance(Args... args);
    static void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }
private:
template <typename... Args>
    Singleton(Args... args)
    :_pdata(new T(args...))
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
        delete _pdata;
    }
private:
    static Singleton* _pInstance;
    T* _pdata;
};

template <typename T>
Singleton<T>* Singleton<T>::_pInstance = nullptr;

template <typename T> 
template <typename... Args>
T* Singleton<T>::getInstance(Args... args)
{
    if(!_pInstance)
    {
        _pInstance = new Singleton(args...);
        atexit(destroy);
    }
    return _pInstance->_pdata;
}



int main()
{
    Computer * p1 = Singleton<Computer>::getInstance();
    //Computer * p1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer * p2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    p1->print();
    p2->print();
    Point* p3 = Singleton<Point>::getInstance();
    //Point* p3 = Singleton<Point>::getInstance(1, 2);
    Point* p4 = Singleton<Point>::getInstance(1, 2);
    p3->print();
    p4->print();
                     
    return 0;
}

