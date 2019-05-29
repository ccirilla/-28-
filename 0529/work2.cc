#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class TextQuery
{
public:
    void readFile(const string filename);
    void query(const string & word);
private:
    map<string, set<int> > _word_Line;
    map<string, int> _word_count;
    vector<string> _line;
};

void TextQuery::readFile(const string filename)
{
    ifstream is(filename);
    string line;
    while(getline(is,line))
        _line.push_back(line);
    is.close();
    int i=1;
    string word;
    for(const auto &s :_line)
    {
        stringstream ss(s);
        while(ss >> word)
        {
            ++_word_count[word];
            _word_Line[word].insert(i);
        }
        ++i;
    }
}

void TextQuery::query(const string & word)
{
    cout <<"-----------------------------------------------"<<
        "----------------------------------------------"<<endl;
    auto ret = _word_count.find(word); 
    if(ret == _word_count.end())
        cout << "\""<<word <<"\""<< " dont in this text" << endl;
    else
    {
        cout<< "\""<<word<<"\"" <<" occurs " << ret->second 
            << " times." << endl;
        for(const auto &s:_word_Line[word])
        {
            cout << "       " << "(line " << s << ") "
                << _line[s-1] << endl;
        }
    }
    cout <<"-----------------------------------------------"<<
        "----------------------------------------------"<<endl;
}


int main()
{
    string  queryWord;
    TextQuery tq;
    tq.readFile("china_daily.txt");
    cout << "Input your want query word" << endl;
    while(cin >> queryWord)
    {
        tq.query(queryWord);            
        cout << "Input your want query word" << endl;
    }
    cout << "Bye~ Bye~" << endl;
    return 0;
}

