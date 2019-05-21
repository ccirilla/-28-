#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class SingLeton
{
public:
    static SingLeton* getInstance()
    {
        if(!_pInstance)
        {
            _pInstance = new SingLeton();
            atexit(destroy);
        }
        return _pInstance;
    }
    void print() { cout << "print()" << endl;  }
    static void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }
private:
    SingLeton() {cout <<"SingLeton()" << endl; }
    ~SingLeton() {cout <<"~SingLeton()" << endl; }
private:
    static SingLeton * _pInstance;
};

SingLeton * SingLeton::_pInstance = getInstance();




int main()
{
    SingLeton::getInstance()->print();
    return 0;
}

