#include <regex>
#include <cassert>
#include <fstream>
#include <stdlib.h>
#include "rssReader.h"

RssReader *RssReader::_pInstance = nullptr;
pthread_once_t RssReader::_once = PTHREAD_ONCE_INIT;

RssReader::RssReader(){
    cout << "RssReader()" <<endl;
}
RssReader::~RssReader(){
    cout << "~RssReader()" <<endl;
}
void RssReader::destroy(){
    if(_pInstance)
        delete _pInstance;
}
void RssReader::ainit()
{
    _pInstance = new RssReader();
    atexit(destroy);
}
RssReader * RssReader::getInstance()
{
    pthread_once(&_once,ainit);
    return _pInstance;
}

void RssReader::parseRss(const char * xmlPath)
{
    XMLDocument doc;
    XMLElement* node = init(doc,xmlPath);
    addInfo(node,_rss);
    node = node->FirstChildElement("item");
    while(node != nullptr)
    {
        addInfo(node,_rss);
        node = node->NextSiblingElement("item");
    }
}

void RssReader::dump(const string & filename)
{
    ofstream os;
    os.open(filename);
    os << *this;
    os.close();
}

ofstream & operator << (ofstream &os,const RssReader &rhs)
{
    string tmp;
    int i = 0;
    for(auto s:rhs._rss)
    {
        os << "<doc>" << endl;
        os << "  " << "<docid>"<< ++i << "</docid>" << endl;
        os << "  " << "<title>" << s.title << "/<title>" <<endl;
        os << "  " << "<link>" << s.link << "/<link>" <<endl;
        os << "  " << "<content>" << s.content << "/<content>" <<endl;
        os << "</doc>" << endl;

        /*os << "time: " << i++ << " ------------------------------"<<endl;
        os << "title: " << s.title << endl;
        os << "link: " << s.link << endl;
        os << "description: "<< s.description << endl;
        tmp.assign(s.content.begin(),s.content.begin()+1000);
        os << "head -100 content :" << endl;
        os << tmp << endl;
        tmp.assign(s.content.end()-1000,s.content.end());
        os << "tril -100 content :" << endl;
        os << tmp << endl;*/
    }
    return os;
}


XMLElement* init(XMLDocument &doc,const char * xmlPath)
{
    int ret;
    ret = doc.LoadFile(xmlPath);
    assert(ret ==0);
    XMLElement* root=doc.RootElement();
    XMLElement* channel = root->FirstChildElement("channel");
    return channel;
}

void addInfo(XMLElement* node,vector<RssItem> &rss)
{
    regex patten("<[^>]*>");
    RssItem tmp;
    XMLElement* pn = node->FirstChildElement("title");
    tmp.title = pn->GetText();
    pn = node->FirstChildElement("link");
    tmp.link = pn->GetText();
    pn = node->FirstChildElement("description");
    tmp.description = pn->GetText();
    tmp.description = regex_replace(tmp.description,patten,"");
    pn = node->FirstChildElement("content:encoded");
    if(pn)
    {
        tmp.content = pn->GetText();
        tmp.content = regex_replace(tmp.content,patten,"");
    }
    rss.push_back(tmp);
}




int main()
{
    ParseRss("coolshell.xml");
    Dump("pagelib.txt");
    return 0;
}

