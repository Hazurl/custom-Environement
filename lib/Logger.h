#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <unordered_set>

//          COLOR
#define RST  "\033[0m"
#define KRED  "\033[31m"
#define KGRN  "\033[32m"
#define KYEL  "\033[33m"
#define KBLU  "\033[34m"
#define KMAG  "\033[35m"
#define KCYN  "\033[36m"
#define KWHT  "\033[37m"

#define FRED(x) KRED << x << RST
#define FGRN(x) KGRN << x << RST
#define FYEL(x) KYEL << x << RST
#define FBLU(x) KBLU << x << RST
#define FMAG(x) KMAG << x << RST
#define FCYN(x) KCYN << x << RST
#define FWHT(x) KWHT << x << RST

#define BOLD(x) "\033[1m" << x << RST
#define UNDL(x) "\033[4m" << x << RST

class Logger {
public:
//          LEVEL DEBUG (Flag)
    static const unsigned int Error = 1;
    static const unsigned int Warning = 2;
    static const unsigned int Log = 4;
    static const unsigned int Info = 8;
    static const unsigned int Verbose = 16;
    static const unsigned int All = Error | Warning | Log | Info | Verbose;

    static void error (std::string msg) { Logger::get()._error(msg); }
    static void warning(std::string msg) { Logger::get()._warning(msg); }
    static void log(std::string msg) { Logger::get()._log(msg); }
    static void info(std::string msg) { Logger::get()._info(msg); }
    static void verbose(std::string msg) { Logger::get()._verbose(msg); }

    static std::ostream& getErrorStream() { return Logger::get()._getErrorStream(); }
    static std::ostream& getWarningStream() { return Logger::get()._getWarningStream(); }
    static std::ostream& getLogStream() { return Logger::get()._getLogStream(); }
    static std::ostream& getInfoStream() { return Logger::get()._getInfoStream(); }
    static std::ostream& getVerboseStream() { return Logger::get()._getVerboseStream(); }

    static void redirectTo (unsigned int levels, std::ostream& os) { Logger::get()._redirectTo(levels, os); }
    static void redirectToFile (unsigned int levels, char* const path) { Logger::get()._redirectToFile(levels, path); }

    static void beginSection (std::string name, unsigned int level) { Logger::get()._beginSection(name, level); }
    static void endSection (std::string name) { Logger::get()._endSection(name); }
    static void hideSection (std::string name) { Logger::get()._hideSection(name); }
    static void showSection (std::string name, unsigned int level) { Logger::get()._showSection(name, level); }

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

    std::ostream& _getErrorStream() { return s_error; }
    std::ostream& _getWarningStream() { return s_warning; }
    std::ostream& _getLogStream() { return s_log; }
    std::ostream& _getInfoStream() { return s_info; }
    std::ostream& _getVerboseStream() { return s_verbose; }

    void _redirectTo (unsigned int levels, std::ostream& os);
    void _redirectToFile (unsigned int levels, char* const path);

    void _beginSection (std::string name, unsigned int level);
    void _endSection (std::string name);
    void _showSection (std::string name, unsigned int level);
    void _hideSection (std::string name);
    void header (std::string title, std::ostream& os);
    bool showThis();

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

    std::unordered_set<std::string> sectionHide;
    std::unordered_set<std::string> inSections;
};

#endif