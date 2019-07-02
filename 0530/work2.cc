#include <iostream>
#include <stack>
#include <string>
using namespace std;


int main()
{
    string s;
    stack<char> stk;
    cin >> s;

    for(auto a:s)
    {
        switch(a)
        {
        case '(':
        case '[':
        case '{':
            stk.push(a);
            break;
        case ')':
            if(stk.empty() || stk.top() != '('){
                return 0;
            }
            else{
                stk.pop();
            }
            break;
        case ']':
            if(stk.empty() || stk.top() != '['){
                return 0;
            }
            else{
                stk.pop();
            }
            break;
        case '}':
            if(stk.empty() || stk.top() != '{'){
                return 0;
            }
            else{
                stk.pop();
            }
            break;
        }
    }
    if(!stk.empty()){
        return 0;
    }
    else{
        return 1;
    }
}

