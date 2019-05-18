#include "hash.h"
#include <iostream>
#include <string.h>
#include <algorithm>

Hash::Hash()
    :_hash(new node[khashNum]())
{
    cout << "Construct sucessful !" << endl;
}
Hash::~Hash()
{
    delete []_hash;
    _dhsah.clear();
    cout << "Delete sucessful !" << endl;
}
int Hash::H(const char *key)
{
    int h = 0, g;
    while (*key)
    {
        h = (h << 4) + *key++;
        g = h & 0xf0000000;
        if (g)
            h ^= g >> 24;
        h &= ~g;

    }
//    cout << "h = " << h << endl;
    return h % khashNum;
}
int Hash::CH(const char * key,int i)
{
    int h = H(key),r = 0;
    r = (i+1)/2;
    if(i%2==0)
    {
        return (h - r*r + khashNum) % khashNum;
    }
    else
    {
        return (h + r*r) % khashNum;
    }
}
void Hash::insert(const char * str)
{
    int h =0,i;
    for(i = 0; ; ++i)
    {
        h = CH(str,i);
        if(_hash[h].num == 0)
        {
            _hash[h].num ++;
            strcpy(_hash[h].word,str);
            break;
        }else if(strcmp(_hash[h].word,str) == 0)
        {
            _hash[h].num++;
            break;
        }
    }
}

bool comparator(const node*s1,const node*s2)
{
    return s1->num < s2->num;
}

void Hash::qqsort(ofstream &ofs)
{
    char buf[40] = {0};
    for(int i=0 ;i<khashNum; ++i)
        if(_hash[i].num)
            _dhsah.push_back(_hash+i);
    auto abeg = _dhsah.begin(),end = _dhsah.end();
    std::sort(abeg, end, comparator);
    for(auto &p:_dhsah)
    {
        *buf = 0;
        sprintf(buf,"%s%-6s %d",buf,p->word,p->num);
        ofs << buf<< endl;
    }
}
