#include "logger.h"
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
using std::cout;
using std::endl;

Mylogger * Mylogger::getMylogger()
{
    if(_log == nullptr){
        _log = new Mylogger();
    }
    return _log;
}

void Mylogger::error(const char * msg)
{
        _myRecord.error(msg);
        
}
void Mylogger::info(const char * msg)
{
        _myRecord.info(msg);
        
}
void Mylogger::warn(const char * msg)
{
        _myRecord.warn(msg);
        
}

void Mylogger::debug(const char * msg)
{
        _myRecord.debug(msg);
        
}

void Mylogger::setPriority(const string &str)
{
    if(str == "DEBUG")
        _myRecord.setPriority(Priority::DEBUG);
    else if(str == "INFO")
        _myRecord.setPriority(Priority::INFO);
    else if(str == "WARN")
        _myRecord.setPriority(Priority::WARN);
    else if(str == "ERROR")
        _myRecord.setPriority(Priority::ERROR);
}
void Mylogger::destroy(){
    if(_log)
        delete _log;
    cout << "~Mylogger()" << endl;
}
Mylogger::~Mylogger() {
    Category::shutdown();
}

Mylogger * Mylogger::_log = nullptr;
Mylogger::Mylogger()
    :_myRecord(Category::getRoot().getInstance("myRecord"))
{
    PatternLayout * patternLayout1 = new PatternLayout();
    PatternLayout * patternLayout2 = new PatternLayout();
    OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &std::cout);
    FileAppender * fileAppender = new FileAppender("fileAppender","mylog");
   // patternLayout1->setConversionPattern("%d [%c] [%-5p] %m%n");
   // patternLayout2->setConversionPattern("%d [%c] [%-5p] %m%n");
    patternLayout1->setConversionPattern("%d [%-5p] %m%n");
    patternLayout2->setConversionPattern("%d [%-5p] %m%n");
    ostreamAppender->setLayout(patternLayout1);
    fileAppender->setLayout(patternLayout2);
    _myRecord.setAppender(ostreamAppender);
    _myRecord.addAppender(fileAppender);
    _myRecord.setPriority(Priority::DEBUG);
    cout << "Mylogger()" << endl;
}
