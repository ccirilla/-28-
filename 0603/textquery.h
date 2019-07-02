#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
using namespace std;

class QueryResult
{
public:
    QueryResult(string word,shared_ptr<set<int>> lines,
                shared_ptr<vector<string>> file)
    : _word(word)
    , _lines(lines)
    , _file(file)
    {}
    shared_ptr<set<int>> getLines() {
        return _lines;
    }
    friend ostream & operator << (ostream &os,const QueryResult & rhs);
private:
    string _word;
    shared_ptr<set<int>> _lines;
    shared_ptr<vector<string>> _file;
};

ostream & operator << (ostream &os,const QueryResult & rhs)
{
    os << rhs._word << " occurs " << rhs._lines->size() << " times " << endl;
    for(auto num : *rhs._lines)
    {
        os  << "   (line " << num+1 << ") "
            << *(rhs._file->begin()+num) << endl;
    }
    return os;
}


class TextQuery
{
public:
    TextQuery()
    :_file(make_shared<vector<string>>())
    {}
    void readFile(const string filename);
    QueryResult query(const string & word) const;
    shared_ptr<vector<string>> getFile() const{
        return _file;
    }
private:
    map<string, shared_ptr<set<int>> > _word_Line;
    shared_ptr<vector<string>> _file;
};

void TextQuery::readFile(const string filename)
{
    ifstream is(filename);
    string line;
    while(getline(is,line))
        _file->push_back(line);
    is.close();
    int i=0;
    string word;
    for(auto beg = _file->begin();beg != _file->end();beg++)
    {
        string s = *beg;
        stringstream ss(s);
        while(ss >> word)
        {
            auto ret = _word_Line.find(word);
            if(ret == _word_Line.end())
            {
                _word_Line.insert(make_pair(word,make_shared<set<int>>()));
            }
            ret = _word_Line.find(word);
            ret->second->insert(i);
        }
        ++i;
    }
}

QueryResult TextQuery::query(const string & word) const
{
    static shared_ptr<set<int>> nul(new set<int>);
    auto ret = _word_Line.find(word);
    if( ret == _word_Line.end() )
        return QueryResult(word,nul,_file);
    else
        return QueryResult(word,ret->second,_file);
}

