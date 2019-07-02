#ifndef __CACHEMANGER_H__
#define __CACHEMANGER_H__
#include "../include/Cache.h"
#include "../include/Configuration.h"
#include <set>
#include <memory>
#include <vector>

class CacheManager
{
public:
    static CacheManager* getInstance();
    static void destroy();
    void init();
    set<pair<string,string>> & getCache(int idx);
    void periodicUpdateCaches();
    shared_ptr<Cache> getPcache(){
        return _pCache;
    }
private:
    CacheManager();
    ~CacheManager() {}
private:
    static CacheManager* _pInstance;
    int _threadNum;
    int _cacheNum;
    string _path;
    shared_ptr<Cache> _pCache;
    vector<set<pair<string,string>>> _subCache;
};

#endif
