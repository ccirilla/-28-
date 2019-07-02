#include "../include/DictProducer.h"
#include "../include/Mydict.h"
#include "../include/cppjieba/Jieba.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>
#include <cctype>



DictProducer::DictProducer()
{
    addEnFiles();
    addCnFiles();
}

void DictProducer::addEnFiles()
{
    string path = Configuration::getInstance()->getConfigMap()["enLibPath"];
    struct dirent* pDirInfo;
    DIR* pDir;
    pDir = opendir(path.c_str());
    if(pDir == nullptr){
        perror("opendir");
        return;
    }
    while((pDirInfo = readdir(pDir)) != nullptr)
    {
        if(*(pDirInfo->d_name) != '.')
            _enFiles.push_back(path+string(pDirInfo->d_name));
    }
    closedir(pDir);
    cout << "已读取英文语料库目录信息:" << endl;
    for(auto & s : _enFiles)
        cout << s << endl;
    cout << endl;
}

void DictProducer::addCnFiles()
{
    string path = Configuration::getInstance()->getConfigMap()["cnLibPath"];
    struct dirent* pDirInfo;
    DIR* pDir;
    pDir = opendir(path.c_str());
    if(pDir == nullptr){
        perror("opendir");
        return;
    }
    while((pDirInfo = readdir(pDir)) != nullptr)
    {
        if(*(pDirInfo->d_name) != '.')
            _cnFiles.push_back(path+string(pDirInfo->d_name));
    }
    closedir(pDir);
    cout << "已读取中文语料库目录信息" << endl;
    for(auto & s : _cnFiles)
        cout << s << endl;
    cout << endl;
}

void DictProducer::buildDict()
{
    for(auto & path : _enFiles)
    {
        fstream fs(path);
        if(!fs){
            perror("fopen");
            return;
        }
        char ch;
        while(fs >> ch)
        {
            if(isupper(ch)){
                ch = tolower(ch);
                fs.seekg(-1,ios_base::cur);
                fs << ch;
            }else if(ispunct(ch)){
                fs.seekg(-1,ios_base::cur);
                fs << ' ';
            }
        }
        fs.clear();
        fs.seekg(0,ios_base::beg);
        string word;
        while(fs >> word)
        {
            _enDict[word]++;
        }
        fs.close();
    }
    cout << "已读取英文语料库中所有单词 : "<< _enDict.size() << "个" << endl;
}

void DictProducer::buildCnDict()
{
    using namespace cppjieba;
    Jieba jieba("../include/cppjieba/dict/jieba.dict.utf8",
                "../include/cppjieba/dict/hmm_model.utf8",
                "../include/cppjieba/dict/user.dict.utf8",
                "../include/cppjieba/dict/idf.utf8",
                "../include/cppjieba/dict/stop_words.utf8");
    for(auto & path : _cnFiles)
    {
        ifstream is(path);
        if(!is){
            perror("fopen");
            return;
        }
        string s;
        while(is >> s)
        {
            vector<string> words;
            jieba.Cut(s,words,true);
            for(auto & word:words)
                _cnDict[word]++;
        }
        is.close();
    }
    cout << "已读取中文语料库中所有单词共 : " << _cnDict.size() << "个" << endl;
    cout << endl;
}

void DictProducer::storeDict()
{
    string path = Configuration::getInstance()->getConfigMap()["dictDataPath"];
    ofstream os(path);
    if(!os){
        perror("fopen");
        return;
    }
    os << _enDict.size() << "\n";
    for(auto& word: _enDict)
    {
        os << word.first << " " 
           << word.second << "\n";
    }
    cout << "已将所有英文单词写入磁盘文件" << endl;
    for(auto& word: _cnDict)
    {
        os << word.first << " " 
           << word.second << "\n";
    }
    cout << "已将所有中文单词写入磁盘文件" << endl;
    cout << endl;
    os.close();
}

int main()
{
    Configuration::getInstance("../conf/configure.txt");
    {
    DictProducer dictproducer;
    dictproducer.buildDict();
    dictproducer.buildCnDict();
    dictproducer.storeDict();
    }
    Mydict::getInstance()->init();
    Mydict::getInstance()->store();
    //Mydict::getInstance()->printIndex();
    return 0;
}

