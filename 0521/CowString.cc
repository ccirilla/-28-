#include <cassert>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

class CowString
{
public:
    class CharProxy
    {
    public:
        CharProxy(CowString &str,int idx);
        operator char()const
        {
            return _str._pstr[_idx];
        }
        CharProxy & operator = (char ch);
        friend std::istream & operator >> (std::istream &is,CowString::CharProxy & rhs);
    private:
        CowString & _str;
        int _idx;
    };
    friend CharProxy;
    friend std::istream & operator >> (std::istream &is,CowString::CharProxy & rhs);

    CowString():_pstr(new char[5]() +4) {
        initRefcount();
        cout << "CowString()" << endl;
    }
    CowString(const char * str)
        :_pstr(new char[strlen(str)+5]() +4)
    {
        initRefcount();
        strcpy(_pstr,str);
        cout << "CowString(const char * )" << endl;
    }
    CowString (const CowString &rhs)
        :_pstr(rhs._pstr)
    {
        increaseRefcount();
        cout << "CowString(const CowString &)" << endl;
    }
    ~CowString() 
    {
        release();
    }

    size_t size() const { return strlen(_pstr); }
    const char * c_str()const  { return _pstr; }
    CowString & operator = (const CowString &rhs);
    CharProxy operator[](int idx);
    friend std::ostream & operator<<(std::ostream & os, const CowString & rhs);

    int getRefcount() { return  *((int*)(_pstr - 4)) ;}
private:
    void initRefcount() {   *((int*)(_pstr - 4)) = 1; }
    void increaseRefcount() {   ++*((int*)(_pstr - 4)); }
    void decreaseRefcount() {   --*((int*)(_pstr - 4)); }
    void release(){
        decreaseRefcount();
        if(getRefcount() == 0)
            delete (_pstr - 4);
        cout << ">>> delete data!" << endl;
    }
private:
    char * _pstr;
};

CowString & CowString::operator = (const CowString &rhs)
{
    if(this != &rhs)
    {
        release();
        _pstr = rhs._pstr;
        increaseRefcount();
    }
    return *this;
}
CowString::CharProxy CowString::operator[](int idx)
{
    assert(idx >= 0 && idx < size());
    return CharProxy(*this,idx);
}
std::ostream & operator<<(std::ostream & os, const CowString & rhs)
{
    os << rhs._pstr;
    return os;
}

CowString::CharProxy::CharProxy(CowString &str,int idx)
    :_str(str)
     ,_idx(idx)
{}
CowString::CharProxy & CowString::CharProxy::operator = (char ch)
{
    char *tmp = new char[_str.size()+5]()+4;
    strcpy(tmp,_str._pstr);
    _str.release();
    _str._pstr = tmp;
    _str.initRefcount();
    _str._pstr[_idx] = ch;
    return *this;
}
std::istream & operator >> (std::istream &is, CowString::CharProxy & rhs) //rhs是左值
{
    char *tmp = new char[rhs._str.size()+5]()+4;
    strcpy(tmp,rhs._str._pstr);
    rhs._str.release();
    rhs._str._pstr = tmp;
    rhs._str.initRefcount();
    is >> rhs._str._pstr[rhs._idx];
    return is;
}

int main(void)
{
    CowString s0;
    cout << "s0 = " << s0 << endl;

    CowString s1("hello,world");
    CowString s2(s1);

    CowString s3("shenzhen");
    s3[0] = 'S';//refcount = 1

    s3 = s2;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    cout << "s1's refcount() = " << s1.getRefcount() << endl;
    cout << "s2's refcount() = " << s2.getRefcount() << endl;
    cout << "s3's refcount() = " << s3.getRefcount() << endl;

    cout << endl << ">>> 执行s1[0] = 'x' 之后:" << endl; 
    s1[0] = 'x';
//    cin >> s1[0];
//    CowString::CharProxy cp;
//    cin >> cp;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    cout << "s1's refcount() = " << s1.getRefcount() << endl;
    cout << "s2's refcount() = " << s2.getRefcount() << endl;
    cout << "s3's refcount() = " << s3.getRefcount() << endl;

    cout << endl << ">>> 执行 cout << s2[0] << endl 之后:" << endl; 
    cout << "s2[0] = " << s2[0] << endl;// 在这里不应该进行深拷贝
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    cout << "s1's refcount() = " << s1.getRefcount() << endl;
    cout << "s2's refcount() = " << s2.getRefcount() << endl;
    cout << "s3's refcount() = " << s3.getRefcount() << endl;

    return 0;

}
