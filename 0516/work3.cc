#include "hash.h"
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <fstream>

class Dictionary
{
public:
    void read(const std::string & filename);
    void store(const std::string & filename);
private:
    Hash _hash;
    stringstream ss;
};

void Dictionary::read(const std::string & filename)
{
    ifstream ifs ;
    ifs.open(filename,std::ios::ate);
    if(!ifs)
    {
        cout << "open file error !" << endl;
        return;
    }
    int len = ifs.tellg();
    ifs.seekg(0);
    char *p = new char[len+1]();
    ifs.read(p,len);
    ss << p;
    ifs.close();
    char buf[30] = {0};
    while(ss)
    {
        ss >> buf;
    //    ss.get();
        _hash.insert(buf);
    }
}
void Dictionary::store(const std::string & filename)
{
    ofstream ofs;
    ofs.open(filename);
    _hash.qqsort(ofs);
    ofs.close();
}


int main()
{
    timeval start,end;
    gettimeofday(&start,NULL);
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("word.txt");
    gettimeofday(&end,NULL);
    cout<<"读取+排序+输出共用时: " << (1000000*(end.tv_sec-start.tv_sec)
                                     +end.tv_usec-start.tv_usec) 
        << " us" <<endl;
    return 0;
}

