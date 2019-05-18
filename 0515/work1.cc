#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(!_pInstance){
            _pInstance = new Singleton;
        }
        return _pInstance;
    }
    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
            _pInstance = NULL;
        }
    }
    void print()
    {
        cout << "print()" << endl;
    }
private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }
    
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = NULL;

int main()
{
    Singleton::getInstance()->print();
    Singleton::getInstance()->destroy();
    return 0;
}

