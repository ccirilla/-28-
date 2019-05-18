#include "queue.h"

int main()
{
    Queue que(3);
    que.back();
    que.pop();
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);
    cout << "QUE front = " << que.front() << endl;
    cout << "QUE rear  = " << que.back() << endl;
    que.pop();
    cout << "QUE front = " << que.front() << endl;
    return 0;
}

