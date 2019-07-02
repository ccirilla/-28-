#include <iostream>
#include <unordered_set>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};


    unordered_set<string> dict(wordList.begin(),wordList.end());
    queue<string> que;
    unordered_set<string> visited;
    visited.insert(beginWord);
    que.push(beginWord);
    int ret = 1;
    while(!que.empty())
    {
        ++ret;
        int times = que.size();
        while(times--)
        {
            string s = que.front();
            que.pop();
            int sz = s.size();
            for(int i=0;i<sz;i++)
            {
                for(char ch='a';ch <='z';ch++)
                {
                    string tmp = s;
                    tmp[i] = ch;
                    if(dict.count(tmp) && tmp == endWord)
                    {
                        return ret;
                    }
                    if(!dict.count(tmp) || visited.count(tmp))
                        continue;
                    visited.insert(tmp);
                    que.push(tmp);
                }
            }

        }
    }
    return 0;
}
