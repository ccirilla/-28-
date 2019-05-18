#include "queue.h"

Queue::Queue(int capacity )
{
    _front = _rear = NULL;
    _capacity = capacity;
    _num = 0;
    cout << "I am Construcor " << endl;
}
Queue:: ~Queue()
{
    cout << "Destorying ~" << endl;
    node *p;
    while(_front != _rear)
    {
        p = _front;
        _front = _front->next;
        cout << p->data << "-->";
        delete p;
    }
    if(_rear)
    {
        cout << _rear->data << "-->";
        delete _rear;
    }
    cout << "NULL" <<endl;
}
bool Queue::emty()
{
    return _rear == NULL;
}
bool Queue::full()
{
    return _num == _capacity;
}
void Queue::push(int n)
{
    if(!full())
    {
        if(emty())
        {
            _front = _rear = new node();
            _rear->data = n;
            _rear->next = NULL;
        }else
        {
            _rear->next = new  node();
            _rear = _rear->next;
            _rear->data = n;
            _rear->next = NULL;
        }
        ++_num; 
    }else
    {
        cout << "Error!,Queue full" << endl;
    }
}
void Queue::pop()
{
    if(!emty())
    {
        node *p = _front;
        if(_front == _rear)
            _front = _rear = NULL;
        else
            _front = _front->next;
        delete p;
        --_num;
    }else
        cout << "Error!,Queue emty" << endl;
}
int Queue::front()
{
    if(!emty())
        return _front->data;
    else
    {
        cout << "Error!,Queue emty" << endl;
        return -1;
    }
}
int Queue::back()
{
    if(!emty())
        return _rear->data;
    else
    {
        cout << "Error!,Queue emty" << endl;
        return -1;
    }
}
