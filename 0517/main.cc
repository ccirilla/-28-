#include "logger.h"
#include <iostream>

int main()
{
    SetLogPriority("WARN");
    LogInfo(" -_- IG 输了！！！");
    LogWarn(" -_- IG 输了！！！");
    LogDebug(" -_- IG 输了！！！");
    LogError(" -v- 决赛: G2 VS TL ");
    LogDestory();
    return 0;
}

