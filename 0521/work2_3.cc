#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;


class SingLetion
{
public:
    static SingLetion* getInstance()
    {
        pthread_once(&_once,init);
        return _pInstance;
    }
    static void init()
    {
        _pInstance = new SingLetion();
        atexit(destory);
    }
    static void destory()
    {
        if(_pInstance)
            delete _pInstance;
    }
    void print() { cout << "print()" << endl;  }
private:
    SingLetion() { cout<<"SingLetion()" << endl; }
    ~SingLetion() { cout<<"~SingLetion()" << endl; }
private:
    static SingLetion* _pInstance;
    static pthread_once_t _once;
};

pthread_once_t SingLetion::_once = PTHREAD_ONCE_INIT;
SingLetion* SingLetion::_pInstance = nullptr;

int main()
{
    SingLetion::getInstance()->print();
    return 0;
}

