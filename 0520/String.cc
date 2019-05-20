#include "String.h"
#include <cassert>
#include <cctype>
#include <string.h>

using std::cout;
using std::endl;
using std::cin;
const int min = 5;

String::String()
:_pstr(new char[1]())
{}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr)+1]())
{
    strcpy(_pstr,pstr);
}
String::~String()
{
    delete []_pstr;
}

String::String(const String &str)
:String(str._pstr)
{}

String & String::operator=(const String & str)
{
    if(_pstr  != str._pstr)
    {
        delete []_pstr;
        _pstr = new char[strlen(str._pstr)+1]();
        strcpy(_pstr,str._pstr);
    }
    return *this;
}

String & String::operator+=(const String &str)
{
    char *temp = new char[strlen(str._pstr)+strlen(_pstr)+1]();
    strcpy(temp,_pstr);
    strcat(temp,str._pstr);
    delete []_pstr;
    _pstr = temp;
    return *this;
}

char & String::operator[](std::size_t index)
{
    assert(index < size());
    return _pstr[index];
}

const char & String::operator[](std::size_t index) const
{
    assert(index < size());
    return _pstr[index];
}

std::size_t String::size() const
{
    return strlen(_pstr);
}

const char* String::c_str() const
{
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs)
{
    return !(strcmp(lhs._pstr,rhs._pstr));
}
bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const String &lhs, const String &rhs)
{
    return ((strcmp(lhs._pstr,rhs._pstr)) <0);
}
bool operator>(const String &lhs, const String &rhs)
{
    return ((strcmp(lhs._pstr,rhs._pstr)) >0);
}
bool operator<=(const String &lhs, const String &rhs)
{
    return !(lhs > rhs);
}
bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}
std::istream &operator>>(std::istream &is, String &s)
{
    assert(is);
    delete []s._pstr;
    s._pstr = new char [min]();
    int capacity = min,n = 0;
    char ch,*temp;
    cout << "input start   capacity = " << capacity << endl;
    while(is.get(ch) && !isspace(ch))
    {
        ++n;
        if(n == capacity)
        {
            capacity *= 2;
            temp = new char [capacity]();
            strcpy(temp,s._pstr);
            delete []s._pstr;
            s._pstr = temp;
            cout << "capacity = " << capacity << endl;
        }
        s._pstr[n-1] = ch;
    }
    return is;
}

String operator+(const String & lhs, const String & rhs)
{
    String temp(lhs);
    temp += rhs;
    return temp;
}











int main()
{
    String s1,s2("aaaaaaaaaaaaaaaa");
    String s3(s2);
    cout << "String s1,s2(\"aaaaaaaaaaaaaaaa\") " << endl;
    cout << "String s3(s2)"<<endl;
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "s3 = " << s3 <<endl;
    cout << "---------------------------------" << endl;
    s2 = "bbbbbbbbbbbbbbbbbb";
    s1 = s2;
    cout << "s2 = \"bbbbbbbbbbbbbbbbbb\" "<<endl;;
    cout << "s1 = s2" <<endl;;
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "---------------------------------" << endl;
    s3 = "cccccccccccccccccc";
    s1 += s3;
    s2 += "cccccccccccccccccc";
    cout << "s3 = \"cccccccccccccccccc\" "<<endl;
    cout << "s1 += s3" <<endl;
    cout << "s2 += \"cccccccccccccccccc\" " <<endl;
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "---------------------------------" << endl;
    cout <<"s3[2] = 'd'" << endl;
    s3[2] = 'd';
    cout << "s3.c_str = " << s3.c_str() << endl;
    cout << "s3.size() = " << s3.size() << endl;
    cout <<"s3[200] = ?" << endl;
    //cout<< s3[200] << endl;;
    //cout << "---------------------------------" << endl;
    cout <<"s1 == s2 ?  " << (s1 == s2) << endl;
    cout <<"s1 != s2 ?  " << (s1 != s2) << endl;
    cout <<"s2 < s3 ?  " << (s2 < s3) << endl;
    cout <<"s1 <= s2 ?  " << (s1 <= s2) << endl;
    cout << "---------------------------------" << endl;
    cout<< "cin >> s3" <<endl;
    cin >> s3;
    cout << "s3 = " << s3 << endl; 
    cout << "---------------------------------" << endl;
    cout << "s1 + s3 = " << (s1+s3) <<endl;
    cout << "s1 + dddddddddd = " << (s1 + "ddddddddddd") << endl;
    cout << "bbbbbbbbbbbbccccccccccc + s3 = " << ("bbbbbbbbbbcccccccccc" + s3) << endl;
    return 0;
}

