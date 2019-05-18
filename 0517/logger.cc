#include "logger.h"
#include <string.h>
#include <iostream>

int main()
{
    LogInfo(" -_- IG 输了！！！");
    LogWarn(" -_- IG 输了！！！");
    LogDebug(" -_- IG 输了！！！");
    LogError(" -v- 决赛: G2 VS TL ");
    Mylogger::getMylogger()->destroy();
    return 0;
}

