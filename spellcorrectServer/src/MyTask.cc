#include "../include/MyTask.h"
#include "../include/Mydict.h"
#include "../include/json/json.h"
#include <iostream>
#include "../include/CacheManager.h"
#define k 5

extern __thread int threadID;


MyTask::MyTask(const string & word,TcpConnectionPtr conn)
    : _queryWord(word)
    , _resultStr("")
      , _conn(conn)
{}

void MyTask::process()
{
    auto pCache = CacheManager::getInstance()->getPcache();
    auto &sSet = CacheManager::getInstance()->getCache(threadID);
    string result = pCache->get(_queryWord);
    if(result == "-1")
    {
        cout << "线程: " << threadID << " 缓存未命中" << endl ;
        queryIndexTable();
        Json::Value words;
        Json::FastWriter writer;
        int i = 0;
        while(!_resultQue.empty() && (i++ < k))
        {
            cout << ">> " << _resultQue.top()._word << " "
                          << _resultQue.top()._dist << " "
                          << _resultQue.top()._freq << endl;
            string idx = "候选词"+string(1,'0'+i);   
            words[idx] = _resultQue.top()._word;
            _resultQue.pop();
        }
        cout << endl;
        result = writer.write(words);
    }
    else{
        cout << "线程: " << threadID << " 缓存命中" << endl << endl;
    }
    /*priority_queue<MyResult,vector<MyResult>,MyCompare> tmmp = _resultQue;
    while(!tmmp.empty())
    {
        auto s = tmmp.top();
        tmmp.pop();
        cout << s._word << " " <<  s._freq << " " << s._dist << endl;
    }
    */
    sSet.insert(make_pair(_queryWord,result));
//    CacheManager::getInstance()->periodicUpdateCaches();
    _conn->sendInLoop(result);
}

void MyTask::queryIndexTable()
{
    set<int> iset = getIndexSet();
    statistic(iset);
}

set<int> MyTask::getIndexSet()
{
    Mydict * p = Mydict::getInstance();
    map<string,set<int>>& _indexTable = p->getIndexTable();
    set<int> iset;
    int cur = 0;
    while(cur != (int)_queryWord.size())
    {
        int len = p->getCnwordLenth(_queryWord[cur]);
        string ch = _queryWord.substr(cur,len);
        cur += len;
        auto iter = _indexTable.find(ch);
        if(iter != _indexTable.end())
        {
            for(int pos : iter->second)
            {
                iset.insert(pos);
            }
        }
    }
    return iset;
}

void MyTask::statistic(const set<int> & iset)
{
    const vector<pair<string,int>> & dict = 
        Mydict::getInstance()->getDict();
    for(auto idx : iset)
    {
        MyResult tmp;
        tmp._word = dict[idx].first;
        tmp._freq = dict[idx].second;
        tmp._dist = distance(tmp._word);
        _resultQue.push(tmp);
    }
}

int MyTask::getmin(int a,int b,int c)
{
    int tmp = a < b ? a:b;
    return (tmp < c ? tmp:c);
}

void MyTask::getArray(vector<string> & array,const string & str)
{
    Mydict * p = Mydict::getInstance();
    int cur = 0;
    while(cur != (int)str.size())
    {
        int len = p->getCnwordLenth(str[cur]);
        array.push_back(str.substr(cur,len));
        cur += len;
    }
}

int MyTask::distance(const string & rhs)
{
    vector<string> row,column;
    getArray(row,rhs);
    getArray(column,_queryWord);
    int len1 = column.size();
    int len2 = row.size();
    int **d = new int*[len1+1];
    for(int i=0;i<=len1;i++){
        d[i] = new int[len2+1];
    }
    int i,j;
    for(i=0;i<=len1;i++){
        d[i][0] = i;
    }
    for(i=0;i<=len2;i++){
        d[0][i] = i;
    }
    for(i=1;i<=len1;i++)
    {
        for(j=1;j<=len2;j++)
        {
            int cost = row[j-1] == column[i-1] ? 0:1;
            int left=d[i-1][j]+1;
            int up=d[i][j-1]+1;
            int sub = d[i-1][j-1]+cost;
            d[i][j] = getmin(left,up,sub);
        }
    }
    int lenth = d[len1][len2];
    for(int i=0;i<=len1;i++)  
    {  
        delete[] d[i];  
    }  
    delete[] d;
    return lenth;
}




