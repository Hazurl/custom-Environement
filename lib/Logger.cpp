#include "Logger.h"

Logger& Logger::get() {
    static Logger instance(std::cout);
    return instance;
}


Logger::Logger (std::ostream& os) :
    s_error(os.rdbuf()), s_warning(os.rdbuf()), s_log(os.rdbuf()), s_info(os.rdbuf()), s_verbose(os.rdbuf()) {
}

Logger::~Logger() {}

void Logger::_error (std::string msg) {
    if (showThis())
        this->s_error << getDateAndHours() << BOLD(FRED("error  ")) << " - " << msg << std::endl;
}

void Logger::_warning(std::string msg) {
    if (showThis())
        this->s_warning << getDateAndHours() << BOLD(FYEL("warning")) << " - " << msg << std::endl;
}

void Logger::_log(std::string msg) {
    if (showThis())
        this->s_log << getDateAndHours() << BOLD(FBLU("log    ")) << " - " << msg << std::endl;
}

void Logger::_info(std::string msg) {
    if (showThis())
        this->s_info << getDateAndHours() << BOLD(FCYN("info   ")) << " - " << msg << std::endl;
}

void Logger::_verbose(std::string msg) {
    if (showThis())
        this->s_verbose << getDateAndHours() << BOLD(FGRN("verbose")) << " - " << msg << std::endl;
}

std::string Logger::getDateAndHours () {
    std::string s = "";

    std::ostringstream os;
    std::time_t t = std::time(NULL);
    char mbstr[100];

    if (printDate) {
        if (printHour) {
            if (std::strftime(mbstr, sizeof(mbstr), "%d/%m/%Y %H:%M:%S", std::localtime(&t))) { os << mbstr; s = os.str(); } 
            else return "";
        } else {
            if (std::strftime(mbstr, sizeof(mbstr), "%d/%m/%Y", std::localtime(&t))) { os << mbstr; s = os.str(); } 
            else return "";
        }
    } else {
        if (printHour) {
            if (std::strftime(mbstr, sizeof(mbstr), "%H:%M:%S", std::localtime(&t))) { os << mbstr; s = os.str(); } 
            else return "";
        } else {
            return "";
        }
    }

    for (int i = s.length(); i < dateHoursSize; i++) // adjust size
        s += " ";

    return s + " ";
}

void Logger::_redirectTo (unsigned int levels, std::ostream& os) {
    if (levels & Logger::Error) {
        if (fileOutError)
            fileOutError.close();
        this->s_error.rdbuf(os.rdbuf());
    }

    if (levels & Logger::Warning) {
        if (fileOutWarning)
            fileOutWarning.close();

        this->s_warning.rdbuf(os.rdbuf());
    }

    if (levels & Logger::Info) {
        if (fileOutInfo)
            fileOutInfo.close();
        this->s_info.rdbuf(os.rdbuf());
    }

    if (levels & Logger::Log) {
        if (fileOutLog)
            fileOutLog.close();
        this->s_log.rdbuf(os.rdbuf());
    }

    if (levels & Logger::Verbose) {
        if (fileOutVerbose)
            fileOutVerbose.close();
        this->s_verbose.rdbuf(os.rdbuf());
    }
}

void Logger::_redirectToFile (unsigned int levels, char* const path) {
    if (levels == 0)
        return;

    if (levels & Logger::Error) {
        if (fileOutError)
            fileOutError.close();

        fileOutError.open(path, std::ios::out | std::ios::app);
        this->s_error.rdbuf(fileOutError.rdbuf());
    }
    
    if (levels & Logger::Warning) {
        if (fileOutWarning)
            fileOutWarning.close();

        fileOutWarning.open(path, std::ios::out | std::ios::app);
        this->s_warning.rdbuf(fileOutWarning.rdbuf());
    }

    if (levels & Logger::Info) {
        if (fileOutInfo)
            fileOutInfo.close();

        fileOutInfo.open(path, std::ios::out | std::ios::app);
        this->s_log.rdbuf(fileOutInfo.rdbuf());
    }

    if (levels & Logger::Log) {
        if (fileOutLog)
            fileOutLog.close();

        fileOutLog.open(path, std::ios::out | std::ios::app);
        this->s_info.rdbuf(fileOutLog.rdbuf());
    }

    if (levels & Logger::Verbose) {
        if (fileOutVerbose)
            fileOutVerbose.close();

        fileOutVerbose.open(path, std::ios::out | std::ios::app);
        this->s_verbose.rdbuf(fileOutVerbose.rdbuf());
    }
}

void Logger::_beginSection (std::string name, unsigned int level) {
    inSections.insert(name);

    if (showThis()) {
        if (level & Logger::Error)
            header(name, s_error << KRED);
        if (level & Logger::Warning)
            header(name, s_warning << KYEL);
        if (level & Logger::Log)
            header(name, s_log << KBLU);
        if (level & Logger::Info)
            header(name, s_info << KCYN);
        if (level & Logger::Verbose)
            header(name, s_verbose << KGRN);
    }
}

void Logger::header (std::string title, std::ostream& os) {
    os << "╔";
    for (unsigned i = 0; i < title.size() + 2; ++i) os << "═";
    os << "╗" << std::endl;
    os << "║ " << title << " ║" << std::endl;
    os << "╚";
    for (unsigned i = 0; i < title.size() + 2; ++i) os << "═";
    os << "╝";
    os << std::endl << RST;
}

void Logger::_endSection (std::string name) {
    inSections.erase(name);
}

void Logger::_showSection (std::string name, unsigned int level) {
    sectionHide.erase(name);
    _beginSection(name, level);
}

void Logger::_hideSection (std::string name) {
    sectionHide.insert(name);
}

bool Logger::showThis() {
    for(auto& s : inSections)
        if (sectionHide.find(s) != sectionHide.end())
            return false;
    return true;
}