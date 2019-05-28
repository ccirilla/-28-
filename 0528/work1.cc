#include <iostream>
#include <string>
using namespace std;

template <typename T,int kmax = 10>
class Queue
{
public:
    Queue()
    :_data(new T[kmax]())
    {
        cout << "Queue()" << endl;
    }
    ~Queue(){
        delete []_data;
        cout << "~Queue()" << endl;
    }
    bool empty(){
        return _front == _rear;
    }
    bool full(){
        return (_rear + 1)%kmax == _front;
    }
    void push(const T & t){
        if(full())
            cout << "The Queue are full , cant push " <<endl;
        else
        {
            _data[_rear] = t;
            _rear = (_rear + 1) % kmax;
        }
    }
    void pop(){
        if(empty())
            cout << "The Queue are empty , cant pop" << endl;
        else
            _front = (_front + 1) % kmax; 
    }
    T front(){
        if(empty())
        {
            cout << "The Queue are empty " << endl;
            return T();
        }
        else
            return _data[_front];
    }
    T back(){
        if(empty())
        {
            cout << "The Queue are empty " << endl;
            return T();
        }
        else
            return _data[(_rear + kmax - 1)%kmax];
    }
    void print();
    int size();
private:
    T* _data;
    int _front = 0;
    int _rear = 0;
};

template <typename T,int kmax>
int Queue<T,kmax>::size()
{
    return (_rear + kmax - _front) % kmax;
}
template <typename T,int kmax>
void Queue<T,kmax>::print()
{
    for(T* it = _data;it!=_data + size();++it)
        cout << *it << " ";
    cout << endl;
}

int test()
{
    Queue<string,5> qstr;
    qstr.front();
    qstr.pop();
    for(int i=0;i<7;i++)
        qstr.push(string(3,'a'+i));
    cout << "back() = " << qstr.back() << endl;
    cout << "front() = " << qstr.front() << endl;
    qstr.print();
    qstr.pop();
    qstr.print();
    for(int i=0;i<5;i++)
        qstr.pop();
    return 0;
}

int main()
{
    Queue<int,5> qstr;
    qstr.front();
    qstr.pop();
    for(int i=0;i<7;i++)
        qstr.push(i);
    cout << "back() = " << qstr.back() << endl;
    cout << "front() = " << qstr.front() << endl;
    qstr.print();
    qstr.pop();
    qstr.print();
    for(int i=0;i<5;i++)
        qstr.pop();
    return 0;
}
