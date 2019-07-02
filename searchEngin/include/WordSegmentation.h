#ifndef _WD_WORD_SEGMENTATION_H_
#define _WD_WORD_SEGMENTATION_H_

#include "Configuration.h"
#include "cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

const char * const DICT_PATH = "/home/luo/project/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/luo/project/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/luo/project/cppjieba/dict/user.dict.utf8";


class WordSegmentation
{
public:
	WordSegmentation()
    : _jieba("../include/cppjieba/dict/jieba.dict.utf8",
                "../include/cppjieba/dict/hmm_model.utf8",
                "../include/cppjieba/dict/user.dict.utf8",
                "../include/cppjieba/dict/idf.utf8",
                "../include/cppjieba/dict/stop_words.utf8")
	{
		cout << "cppjieba init!" << endl;
	}

	map<string,int> operator()(string text)
	{
		vector<string> words;
        map<string,int> tmp;
		_jieba.Cut(text.c_str(), words, true);//cutAll 
        auto stop = Configuration::getInstance()->getStopWordList();
        for(auto &word : words)
        {
            if(stop.count(word) == 0)
            {
                tmp[word]++;
            }
        }
        return tmp;
	}

private:
	cppjieba::Jieba _jieba;
};



#endif
