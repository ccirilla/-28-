#include "../include/CacheManager.h"
#include <iostream>


CacheManager* CacheManager::_pInstance = nullptr;

CacheManager::CacheManager()
:_threadNum(stoi(Configuration::getInstance()->getConfigMap()["threadNum"]))
,_cacheNum(stoi(Configuration::getInstance()->getConfigMap()["cacheNum"]))
, _path(Configuration::getInstance()->getConfigMap()["cacheDataPath"])
,_pCache(new Cache(_cacheNum))
{
    _subCache.resize(_threadNum);
}

CacheManager* CacheManager::getInstance()
{
    if(!_pInstance){
        _pInstance = new CacheManager();
        atexit(destroy);
    }
    return _pInstance;
}

void CacheManager::destroy()
{
    if(_pInstance){
        delete _pInstance;
    }
}

void CacheManager::init()
{
    _pCache->readFromFile(_path);
    cout << "从磁盘中读取缓存: OK" << endl; 
}

set<pair<string,string>> & CacheManager::getCache(int idx)
{
    return _subCache[idx];
}

void CacheManager::periodicUpdateCaches()
{
    vector<set<pair<string,string>>> tmpSet;
    tmpSet.resize(_threadNum);
    _subCache.swap(tmpSet);
    shared_ptr<Cache> tmpPcache(new Cache(*_pCache));
    cout << "原缓存: ";
    _pCache->print();
    cout << endl;
    for(auto &sset : tmpSet)
    {
        for(auto & ppair: sset)
        {
            tmpPcache->addElement(ppair.first,ppair.second);
        }
    }
    _pCache = tmpPcache;
    _pCache->writeToFile(_path);
    cout << "缓存更新 : OK" <<endl;
    _pCache->print();
    cout << endl;
    cout << endl;
}


#if 0
int main()
{
    Configuration::getInstance("../conf/configure.txt");
    CacheManager *p = CacheManager::getInstance();
/*    int i=-1,j=4;
    while(++i < 3)
    {
        for(j=0;j<4;j++)
        {
            p->getCache(j).insert(make_pair(string(1+j,'a'+i),string(1,'A'+i)));
        }
    }
    p->periodicUpdateCaches();
*/
    p->init();
    cout << p->getPcache()->get("aaa") << endl;
    return 0;
}
#endif
