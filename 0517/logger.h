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

#define LogInfo(msg,...)(Mylogger::getMylogger()->info(prefix(msg),##__VA_ARGS__))
#define LogError(msg,...)(Mylogger::getMylogger()->error(prefix(msg),##__VA_ARGS__))
#define LogWarn(msg,...)(Mylogger::getMylogger()->warn(prefix(msg),##__VA_ARGS__))
#define LogDebug(msg,...)(Mylogger::getMylogger()->debug(prefix(msg),##__VA_ARGS__))
#define SetLogPriority(msg)(Mylogger::getMylogger()->setPriority(msg))
#define LogDestory()(Mylogger::destroy())

class Mylogger
{
public:
    static Mylogger * getMylogger();
    void error(const char * msg);
    void warn(const char * msg);
    void info(const char * msg);
    void debug(const char * msg);

    template <typename... Args>
        void warn(Args... args){
            _myRecord.warn(args...);
        }
    template <typename... Args>
        void error(Args... args){
            _myRecord.error(args...);
        }
    template <typename... Args>
        void debug(Args... args){
            _myRecord.debug(args...);
        }
    template <typename... Args>
        void info(Args... args){
            _myRecord.info(args...);
        }
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
