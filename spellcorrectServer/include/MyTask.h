#ifndef __MYTASK_H__
#define __MYTASK_H__
#include "../include/TcpConnection.h"
#include <queue>
#include <vector>
#include <set>
using namespace wd;
using namespace std;

struct MyResult
{
    string _word;
    int _freq;
    int _dist;
};

struct MyCompare
{
    bool operator ()(const MyResult & lhs,const MyResult& rhs)
    {
        if(lhs._dist > rhs._dist){
            return true;
        } else if(lhs._dist < rhs._dist){
            return false;
        } else{
            if(lhs._freq < rhs._freq){
                return true;
            } else if(lhs._freq > rhs._freq){
                return false;
            } else{
                return lhs._word > rhs._word;
            }
        }
    }
};

class MyTask
{
public:
    MyTask(const string & word,TcpConnectionPtr conn);
    void process();
private:
    void queryIndexTable();
    set<int> getIndexSet();
    void statistic(const set<int> & iset);
    int distance(const string & rhs);
    int getmin(int a,int b,int c);
    void getArray(vector<string> & array,const string & str);
private:
    string _queryWord;
    string _resultStr;
    TcpConnectionPtr _conn;
    priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue;
};

#endif
