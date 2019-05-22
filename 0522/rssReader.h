#ifndef __RSS_READER_H__
#define __RSS_READER_H__

#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>


#define ParseRss(msg)(RssReader::getInstance()->parseRss(msg))
#define Dump(msg)(RssReader::getInstance()->dump(msg))


using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    void parseRss(const char * xmlPath);//解析
    void dump(const string & filename);//输出
    friend ofstream & operator << (ofstream &os,const RssReader &rhs);
    static void destroy();
    static void ainit();
    static RssReader *getInstance();
private:
    RssReader();
    ~RssReader();
private:
    static RssReader *_pInstance;
    static pthread_once_t _once;
    vector<RssItem> _rss;
}; 

XMLElement* init(XMLDocument &doc,const char * xmlPath);
void addInfo(XMLElement* node,vector<RssItem> &rss);



#endif
