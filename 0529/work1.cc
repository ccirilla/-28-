#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Dictionary
{
public:
    void read(const std::string & filename);
    void store(const std::string & filename);
private:
//    map<string,int> _word_count;
    unordered_map<string,int> _word_count;
};

void Dictionary::read(const std::string & filename)
{
    ifstream is(filename);
    string word;
    while(is >> word)
    {
        ++_word_count[word];
    }
    is.close();
}

void Dictionary::store(const std::string & filename)
{
    ofstream os(filename);
    //vector<map<string,int>::iterator> vec;
    vector<unordered_map<string,int>::iterator> vec;
    auto in = back_inserter(vec);
    for(auto it = _word_count.begin();it!=_word_count.end();++it)
        in = it;
    //sort(vec.begin(),vec.end(),[](map<string,int>::iterator lhs,map<string,int>::iterator rhs)
    sort(vec.begin(),vec.end(),[](unordered_map<string,int>::iterator lhs,unordered_map<string,int>::iterator rhs)
         {   return lhs->second > rhs->second; });
    for(auto it = vec.begin();it != vec.end();++it)
        os << (*it)->first << "  " << (*it)->second << "\n";
    os.close();
}


int main()
{
    timeval start,end;
    gettimeofday(&start,NULL);
    Dictionary d;
    d.read("The_Holy_Bible.txt");
    d.store("work1.txt");
    gettimeofday(&end,NULL);
    cout<<"读取+排序+输出共用时: " << (1000000*(end.tv_sec-start.tv_sec)
                                       +end.tv_usec-start.tv_usec) 
        << " us" <<endl;
    return 0;
}

