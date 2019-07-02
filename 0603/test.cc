#include <iostream>
#include <memory>

using namespace std;


int * get()
{
    return new int();
}


int main()
{
    unique_ptr<int> pa((get()));
    cout << *pa << endl;
    return 0;
}

