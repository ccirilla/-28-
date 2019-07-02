#ifndef __MYDICT_H__
#define __MYDICT_H__
#include <pthread.h>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;


class Mydict
{
public:
    static Mydict* getInstance(); 
    static void pinit();
    static void destroy();
    void init();
    vector<pair<string,int>>& getDict();
    map<string,set<int>>& getIndexTable();
    void printIndex();
    int getCnwordLenth(char ch);
    void store();
    void read();
private:
    void readDict();
    void buildEnIndex();
    void buildCnIndex();
private:
    Mydict();
    ~Mydict();

private:
    static Mydict* _pInstance;
    static pthread_once_t _once;
    vector<pair<string,int>> _dict;
    int _enWordNum;
    map<string,set<int>> _indexTable;
};

#endif
