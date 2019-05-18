#ifndef __LOGGER_H
#define __LOGGER_H 

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

#define LogInfo(msg)\
{\
    static char temp[100];\
    strcpy(temp,msg);\
    sprintf(temp,"%s- (%s:%d ,%s)",temp,__FUNCTION__,__LINE__,__FILE__);\
    Mylogger::getMylogger()->info(temp);\
}
#define LogError(msg)\
{\
    static char temp[100];\
    strcpy(temp,msg);\
    sprintf(temp,"%s- (%s:%d ,%s)",temp,__FUNCTION__,__LINE__,__FILE__);\
    Mylogger::getMylogger()->error(temp);\
}
#define LogWarn(msg)\
{\
    static char temp[100];\
    strcpy(temp,msg);\
    sprintf(temp,"%s- (%s:%d ,%s)",temp,__FUNCTION__,__LINE__,__FILE__);\
    Mylogger::getMylogger()->warn(temp);\
}

#define LogDebug(msg)\
{\
    static char temp[100];\
    strcpy(temp,msg);\
    sprintf(temp,"%s- (%s:%d ,%s)",temp,__FUNCTION__,__LINE__,__FILE__);\
    Mylogger::getMylogger()->debug(temp);\
}


const int size = 1024;
const int num = 3;


using namespace log4cpp;


class Mylogger
{
public:
    static Mylogger * getMylogger()
    {
        if(_log == nullptr){
            _log = new Mylogger();
        }
        return _log;
    }
    void warn(const char * msg){
        _myRecord.warn(msg);
    }
    void error(const char * msg){
        _myRecord.error(msg);
    }
    void debug(const char * msg){
        _myRecord.debug(msg);
    }
    void info(const char * msg){
        _myRecord.info(msg);
    }
    void destroy(){
        delete _log;  
    }
private:
    Mylogger();
    ~Mylogger() {
        Category::shutdown();
    }
private:
    static Mylogger * _log;
    Category & _myRecord;
    PatternLayout * _patternLayout1;
    PatternLayout * _patternLayout2;
    OstreamAppender * _ostreamAppender;
    RollingFileAppender * _rollingFileAppender;
};

Mylogger * Mylogger::_log = nullptr;
Mylogger::Mylogger()
    :_myRecord(Category::getRoot().getInstance("myRecord"))
    ,_patternLayout1(new PatternLayout())
    ,_patternLayout2(new PatternLayout())
    ,_ostreamAppender(new OstreamAppender("ostreamAppender", &std::cout))
    ,_rollingFileAppender(new RollingFileAppender("rollingFileAppender","work_log",size,num))
    {
        _patternLayout1->setConversionPattern("%d [%-5p] %m%n");
        _patternLayout2->setConversionPattern("%d [%-5p] %m%n");
        _ostreamAppender->setLayout(_patternLayout1);
        _rollingFileAppender->setLayout(_patternLayout2);
        _myRecord.setAppender(_ostreamAppender);
        _myRecord.addAppender(_rollingFileAppender);
        _myRecord.setPriority(Priority::DEBUG);
    }

#endif
