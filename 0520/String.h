//实现String类的其它运算符的重载

#include <iostream>

class String
{
public:
    String();
    String(const char *);
    String(const String &);
    String &operator=(const String &);
 //   String &operator=(const char *);隐式转换
    String &operator+=(const String &);
 //   String &operator+=(const char *);隐式转换
    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;
    std::size_t size() const;
    const char* c_str() const;
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);
    ~String();
private:
    char * _pstr;

private:

};
String operator+(const String &, const String &);
//String operator+(const String &, const char *);隐式转换
//String operator+(const char *, const String &);隐式转换
