#include "../include/Mydict.h"
#include <iostream>
#include "../include/Configuration.h"
#include <fstream>
#include <sstream>


Mydict* Mydict::_pInstance = nullptr;
pthread_once_t Mydict::_once = PTHREAD_ONCE_INIT;

Mydict* Mydict::getInstance()
{
    pthread_once(&_once,pinit);
    return _pInstance;
}

void Mydict::pinit()
{
    if(!_pInstance)
    {
        _pInstance = new Mydict();
        atexit(destroy);
    }
}

void Mydict::destroy()
{
    if(!_pInstance)
        delete _pInstance;
}

vector<pair<string,int>>& Mydict::getDict()
{
    return _dict;
}

map<string,set<int>>& Mydict::getIndexTable()
{
    return _indexTable;
}

Mydict::Mydict()
{
    cout << "Mydict()" << endl;
}

Mydict::~Mydict()
{
    cout << "~Mydict()" << endl;
}

void Mydict::init()
{
    readDict();
    cout << "将单词从磁盘写入词典 :OK" <<endl;
    buildEnIndex();
    cout << "建立英文索引: OK" << endl;
    buildCnIndex();
    cout << "建立中文索引: OK" << endl;
}

void Mydict::readDict()
{
    string path = Configuration::getInstance()->getConfigMap()["dictDataPath"];
    ifstream is(path);
    if(!is)
    {
        perror("fopen");
        return;
    }
    is >> _enWordNum;
    string word;
    int times;
    while(is >> word >> times)
    {   
        _dict.push_back(make_pair(word,times));
    }
}

void Mydict::buildEnIndex()
{
    for(char ch = 'a';ch <= 'z';ch++)
    {
        for(int idx =0; idx < _enWordNum; idx++)
        {
            string word = _dict[idx].first;
            if(word.find(ch) != string::npos)
            {
                _indexTable[string(1,ch)].insert(idx);
            }
        }
    }
}

void Mydict::printIndex()
{
    for(auto & par:_indexTable)
    {
        cout << par.first << "--> ";
        for(auto idx : par.second)
        {
            cout << _dict[idx].first << ":" << _dict[idx].second << " ";
        }
        cout << endl;
    }
}

void Mydict::buildCnIndex()
{
    for(int k = _enWordNum;k!= (int)_dict.size();k++)
    {
        string Wordd = _dict[k].first;
        int cur = 0;
        while(cur != (int)Wordd.size())
        {
            int len = getCnwordLenth(Wordd[cur]);
            string ch = Wordd.substr(cur,len);
            cur += len;
            if(_indexTable.find(ch) == _indexTable.end())
            {
                for(int idx =_enWordNum; idx < (int)_dict.size(); idx++)
                {
                    string word = _dict[idx].first;
                    if(word.find(ch) != string::npos)
                    {
                        _indexTable[ch].insert(idx);
                    }
                }

            }
        }
    }
}

int Mydict::getCnwordLenth(char ch)
{
    if(ch & (1<<7))
    {
        int nBytes = 1;
        for(int idx =0;idx !=6;idx++)
        {
            if(ch & (1<<(6-idx)))
            {
                nBytes++;
            }
            else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

void Mydict::store()
{
    ofstream os(Configuration::getInstance()->getConfigMap()["dictIndexPath"]);
    for(auto & ele :_indexTable)
    {
        os << ele.first << " ";
        for(auto idx : ele.second)
        {
            os << idx << " ";
        }
        os << '\n';
    }
    os.close();
}

void Mydict::read()
{
    readDict();
    ifstream is(Configuration::getInstance()->getConfigMap()["dictIndexPath"]);
    if(!is){
        perror("fopen");
    }
    string line;
    while(getline(is,line))
    {
        stringstream ss(line);
        string word;
        ss >> word;
        int k;
        while(ss >> k)
        {
            _indexTable[word].insert(k);
        }
    }
}


