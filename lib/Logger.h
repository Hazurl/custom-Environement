#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <assert.h>

//          COLOR
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED << x << RST
#define FGRN(x) KGRN << x << RST
#define FYEL(x) KYEL << x << RST
#define FBLU(x) KBLU << x << RST
#define FMAG(x) KMAG << x << RST
#define FCYN(x) KCYN << x << RST
#define FWHT(x) KWHT << x << RST

#define BOLD(x) "\x1B[1m" << x << RST
#define UNDL(x) "\x1B[4m" << x << RST

//          LEVEL DEBUG (Flag)
#define Error 1
#define Warning 2
#define Log 4
#define Info 8
#define Verbose 16

class Logger {
public:

    static void error (std::string msg) { Logger::get()._error(msg); }
    static void warning(std::string msg) { Logger::get()._warning(msg); }
    static void log(std::string msg) { Logger::get()._log(msg); }
    static void info(std::string msg) { Logger::get()._info(msg); }
    static void verbose(std::string msg) { Logger::get()._verbose(msg); }

    static void redirectTo (unsigned int levels, std::ostream& os) { Logger::get()._redirectTo(levels, os); }
    static void redirectToFile (unsigned int levels, std::string path) { Logger::get()._redirectToFile(levels, path); }

    static void setDatePrinting (bool b)  { Logger::get()._setDatePrinting(b); }
    static void setHourPrinting (bool b)  { Logger::get()._setHourPrinting(b); }
    static void setMinimumDateHoursSize (int len)  { Logger::get()._setMinimumDateHoursSize(len); }

private:
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
    static Logger& get();

    void _error (std::string msg);
    void _warning(std::string msg);
    void _log(std::string msg);
    void _info(std::string msg);
    void _verbose(std::string msg);

    void _redirectTo (unsigned int levels, std::ostream& os);
    void _redirectToFile (unsigned int levels, std::string path);

    void _setDatePrinting (bool b) { printDate = b; };
    void _setHourPrinting (bool b) { printHour = b; };
    void _setMinimumDateHoursSize (int len) { dateHoursSize = len; }


    Logger(std::ostream& os);
    ~Logger();
    std::string getDateAndHours ();

    std::ostream s_error; 
    std::ofstream fileOutError;

    std::ostream s_warning; 
    std::ofstream fileOutWarning;

    std::ostream s_log; 
    std::ofstream fileOutLog;

    std::ostream s_info; 
    std::ofstream fileOutInfo;

    std::ostream s_verbose; 
    std::ofstream fileOutVerbose;

    bool printHour = true;
    bool printDate = false;
    int dateHoursSize = 0;
};

#endif