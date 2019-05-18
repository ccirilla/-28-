#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
const int kStack_capacity = 10;
class Stack
{
public:
    static Stack * getInstance(int capacity = 10)
    {
        if(!_pInstance){
            _pInstance = new Stack(capacity);
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
    bool emty()
    {
        return _top == -1;
    }
    bool full()
    {
        return _top == _capacity -1;
    }
    void push(int num)
    {
        if(!full())
            _data[++_top] = num;
        else
            exit(0);
    }
    void pop()
    {
        if(!emty())
            --_top;
    }
    int top()
    {
        if(!emty())
            return _data[_top];
        else
            exit(0);
    }
private:
    Stack(int capacity)
    {
        _top = -1;
        _capacity = capacity;
        cout << "Stack()" << endl;
    }
    ~Stack()
    {
        cout << "~Stack()" << endl;
    }
    
    static Stack * _pInstance;
    int _data[kStack_capacity];
    int _top;
    int _capacity;
};
Stack * Stack::_pInstance = NULL;

int main()
{
    Stack::getInstance(3);
    //cout << "Stack Top = " << Stack::getInstance()->top() << endl;崩溃
    Stack::getInstance()->push(10);
    Stack::getInstance()->push(12);
    Stack::getInstance()->push(14);
    //Stack::getInstance()->push(16);崩溃
    cout << "Stack Top = " << Stack::getInstance()->top() << endl;
    Stack::getInstance()->pop();
    cout << "Stack Top = " << Stack::getInstance()->top() << endl;
    Stack::getInstance()->destroy();
    return 0;
}

