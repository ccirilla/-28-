#ifndef __LOGGER_H
#define __LOGGER_H 

#include <log4cpp/Category.hh>
#include <string>
using std::string;
using namespace log4cpp;

#define prefix(msg)(string("[").append(__FILE__)\
                    .append(":").append(__FUNCTION__)\
                    .append(":").append(std::to_string(__LINE__))\
                    .append("] ").append(msg).c_str()) 

#define LogInfo(msg)(Mylogger::getMylogger()->info(prefix(msg)))
#define LogError(msg)(Mylogger::getMylogger()->error(prefix(msg)))
#define LogWarn(msg)(Mylogger::getMylogger()->warn(prefix(msg)))
#define LogDebug(msg)(Mylogger::getMylogger()->debug(prefix(msg)))
#define SetLogPriority(msg)(Mylogger::getMylogger()->setPriority(msg))
#define LogDestory()(Mylogger::destroy())

class Mylogger
{
public:
    static Mylogger * getMylogger();
    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
    void info(const char * msg);
    static void destroy();
    void setPriority(const string &);
private:
    Mylogger();
    ~Mylogger();
private:
    static Mylogger * _log;
    Category & _myRecord;
};


#endif
