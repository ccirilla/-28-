#include <vector>
#include <fstream>
using namespace std;
const int khashNum = 20000;//哈希表长度


struct node{
    char word[30];//单词
    int num;//词频
};


class Hash
{
public:
    Hash();//构造
    ~Hash();//析构
    int H(const char *str);//哈希散列函数
    int CH(const char * key,int i);//哈希冲突函数
    void insert(const char *str);//向哈希表中插入一个元素
    void qqsort(ofstream &);//索引排序
    //bool isShorter(const node*s1,const node*s2);
private:
    node *_hash;//哈希表
    vector<node*> _dhsah;//哈希索引表
};

