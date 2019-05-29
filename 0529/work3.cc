#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;


class LRUCache {
public:
    LRUCache(int capacity) 
    :_capacity(capacity)
    {}

    int get(int key) 
    {
        auto ret = _map.find(key);
        if(ret == _map.end())
            return -1;
        else
        {
            if(_list.begin() != ret->second)
            {
                _list.emplace_front(key,ret->second->value);
                _list.erase(ret->second);
                ret->second = _list.begin();
            }
            return ret->second->value;
        }
    }

    void put(int key, int value) 
    {
        auto ret = _map.find(key);
        if(ret != _map.end())
        {
            _list.emplace_front(key,value);
            _list.erase(ret->second);
            ret->second = _list.begin();
            return ;
        }
        if(_list.size() == (unsigned long)_capacity)
        {
            _map.erase(_list.back().key);
            _list.pop_back();
        }
        _list.emplace_front(key,value);
        _map.emplace(key,_list.begin());
    }
private:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v) {}
    };
    list<CacheNode> _list;
    unordered_map<int,list<CacheNode>::iterator> _map;
    int _capacity;
};

int main()
{

    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout<<cache.get(1)<<endl;      // 返回  1
    cache.put(3, 3);    // 该操作会使得密钥 2 作废
    cout<<cache.get(2)<<endl;      // 返回  1
    cache.put(4, 4);    // 该操作会使得密钥 1 作废
    cout<<cache.get(1)<<endl;      // 返回  1
    cout<<cache.get(3)<<endl;      // 返回  1
    cout<<cache.get(4)<<endl;      // 返回  1
    return 0;
}

