#include "logger.h"
#include <iostream>

int main()
{
    SetLogPriority("DEBUG");
    LogInfo(" -_- IG 输了！！！%s, %d","hahha",15);
    LogWarn(" -_- IG 输了！！！%-10s,%.3f","ooo",2.3154);
    LogDebug(" -_- IG 输了！！！");
    LogError(" -v- 决赛: G2 VS TL ");
    LogDestory();
    return 0;
}

