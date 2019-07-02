#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String{
public:
    String();
    String(const char * pstr);
//    String(const String &rhs);
    String(String && rhs)
    :_pstr(rhs._pstr)
    {
        rhs._pstr = nullptr;
        cout << "String(String && rhs)" << endl;
    }
    String & operator = (const String &rhs);
    String & operator = (String &&rhs){
        if(this != &rhs){
            delete _pstr;
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
            cout << "String & operator(String && rhs)" << endl;
        }
        return *this;
    }
    ~String();
    void print()
    {
        if(_pstr)
            cout << _pstr << endl;
    }
private:
    char * _pstr;
};

String::String()
{
    _pstr = NULL;
}

String::String(const char * pstr)
:_pstr(new char[strlen(pstr)+1]())
{
    strcpy(_pstr,pstr);
    cout << "String(const char*)" << endl;
}
#if 0
String::String(const String & rhs)
:_pstr(new char[strlen(rhs._pstr)+1]())
{
    strcpy(_pstr,rhs._pstr);
}
#endif
String & String::operator = (const String &rhs)
{
    if(this != &rhs){
        if(_pstr)
            delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
    }
    cout << "1111111111" << endl;
    return *this;
}

String::~String()
{
    if(_pstr)
        delete []_pstr;
}

String test0()
{
    String s1("aaaa");
    return s1;
}

int main(void)
{
    String str1;
    str1.print();
    str1 = "hahaha";
    String str2 = String("Hello,world");
    //String str3("wangdao");
    String str3(test0());
    str2.print();
    str3.print();
//    String str4 = str3;
 //   str4.print();
 //   str4 = str2;
 //   str4.print();

    return 0;
}

