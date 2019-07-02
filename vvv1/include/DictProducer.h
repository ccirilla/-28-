#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include "../include/Configuration.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DictProducer
{
public:
    DictProducer();
    void buildDict();
    void buildCnDict();
    void storeDict();
private:
    void addEnFiles();
    void addCnFiles();
private:
    vector<string> _enFiles;
    vector<string> _cnFiles;
    map<string,int> _enDict;
    map<string,int> _cnDict;
};

#endif
