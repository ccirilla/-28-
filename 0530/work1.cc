#include <iostream>

using namespace std;

template <typename T, typename Compare = std::less<T> >
class HeapSort
{
public:
    HeapSort(T* arr,int size)
    :_arr(arr)
    ,_size(size)
    {}
    void heapAdjust(int ,int);
    void sort();
    void swap(int i,int j){
        T tmp = _arr[i];
        _arr [i] = _arr[j];
        _arr[j] = tmp;
    }
    void print(){
        T *cur = _arr;
        int sz = _size;
        while(sz--)
            cout << *cur++ << " ";
        cout << endl;
    }
private:
    T* _arr;
    int _size;
};

template <typename T, typename Compare >
void HeapSort<T,Compare>::heapAdjust(int pos,int sz)
{
    Compare com;
    T tmp = _arr[pos];
    int k = 2*pos + 1;
    while( k < sz )
    {
        if( (k+1) < sz && com(_arr[k],_arr[k+1]))
            k = k+1;
        if( !com(tmp,_arr[k]) )
            break;
        else{
            _arr[pos] = _arr[k];
            pos = k;
            k = 2*k +1 ;
        }
    }
    _arr[pos] = tmp;
}

template <typename T, typename Compare >
void HeapSort<T,Compare>::sort()
{
    int k = _size / 2;
    while(k >= 0){
        heapAdjust(k,_size);
        --k;
    }
    k = _size -1;
    swap(0,k);
    while(k > 1)
    {
        heapAdjust(0,k);
        --k;
        swap(0,k);
    }
}


int main()
{
    char b[10] = {'s','a','z','o','n','s','u','x','x','p'};
    int a[9] = {5,7,6,8,4,9,3,1,2};
    HeapSort<int>h(a,9);
    h.print();
    h.sort();
    h.print();
    HeapSort<char>h1(b,10);
    h1.print();
    h1.sort();
    h1.print();
    cout << endl;
    return 0;
}

