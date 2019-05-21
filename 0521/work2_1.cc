#include <iostream>
using std::cout;
using std::endl;
class SingLeton
{
    class AutoRelease
    {
    public:
        AutoRelease(){cout << "AutoRelease()"<<endl;}
        ~AutoRelease(){
            if(_pInstance)
                delete _pInstance;
            cout << "~AutoRelease()"<<endl;
        }
    };
public:
    static SingLeton * getInstance()
    {
        if(_pInstance == nullptr)
            _pInstance = new SingLeton();
        return _pInstance;
    }
    void print () { cout <<"print()" << endl;  }
private:
    SingLeton() { cout << "SingLeton()" << endl; }
    ~SingLeton() { cout << "~SingLeton()" << endl; }
private:
    static SingLeton *_pInstance;
    static AutoRelease _autoRelease;
};

SingLeton * SingLeton::_pInstance = nullptr;
SingLeton::AutoRelease SingLeton::_autoRelease;



int main()
{
    SingLeton::getInstance()->print();
    return 0;
}

