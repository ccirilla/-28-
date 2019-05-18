#ifndef  __QUEUE_H__
#define  __QUEUE_H__
#include <iostream>
using std::cout;
using std::endl;

struct node{
    int data;
    node *next;
};

class Queue
{
public:
    Queue(int capacity = 10);
    ~Queue();
    void push(int);
    void pop();
    int front();
    int back();
    bool emty();
    bool full();
private:
    node *_front;
    node *_rear;
    int _capacity;
    int _num;
};

#endif
