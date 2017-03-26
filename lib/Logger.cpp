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
    this->s_error << getDateAndHours() << BOLD(FRED("error  ")) << " - " << msg << std::endl;
}

void Logger::_warning(std::string msg) {
    this->s_warning << getDateAndHours() << BOLD(FYEL("warning")) << " - " << msg << std::endl;
}

void Logger::_log(std::string msg) {
    this->s_log << getDateAndHours() << BOLD(FBLU("log    ")) << " - " << msg << std::endl;
}

void Logger::_info(std::string msg) {
    this->s_info << getDateAndHours() << BOLD(FCYN("info   ")) << " - " << msg << std::endl;
}

void Logger::_verbose(std::string msg) {
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
    if (levels & Error) {
        if (fileOutError)
            fileOutError.close();
        this->s_error.rdbuf(os.rdbuf());
    }

    if (levels & Warning) {
        if (fileOutWarning)
            fileOutWarning.close();

        this->s_warning.rdbuf(os.rdbuf());
    }

    if (levels & Info) {
        if (fileOutInfo)
            fileOutInfo.close();
        this->s_info.rdbuf(os.rdbuf());
    }

    if (levels & Log) {
        if (fileOutLog)
            fileOutLog.close();
        this->s_log.rdbuf(os.rdbuf());
    }

    if (levels & Verbose) {
        if (fileOutVerbose)
            fileOutVerbose.close();
        this->s_verbose.rdbuf(os.rdbuf());
    }
}

void Logger::_redirectToFile (unsigned int levels, std::string path) {
    if (levels == 0)
        return;

    if (levels & Error) {
        if (fileOutError)
            fileOutError.close();

        fileOutError.open(path, std::ios::out | std::ios::app);
        this->s_error.rdbuf(fileOutError.rdbuf());
    }
    
    if (levels & Warning) {
        if (fileOutWarning)
            fileOutWarning.close();

        fileOutWarning.open(path, std::ios::out | std::ios::app);
        this->s_warning.rdbuf(fileOutWarning.rdbuf());
    }

    if (levels & Info) {
        if (fileOutInfo)
            fileOutInfo.close();

        fileOutInfo.open(path, std::ios::out | std::ios::app);
        this->s_log.rdbuf(fileOutInfo.rdbuf());
    }

    if (levels & Log) {
        if (fileOutLog)
            fileOutLog.close();

        fileOutLog.open(path, std::ios::out | std::ios::app);
        this->s_info.rdbuf(fileOutLog.rdbuf());
    }

    if (levels & Verbose) {
        if (fileOutVerbose)
            fileOutVerbose.close();

        fileOutVerbose.open(path, std::ios::out | std::ios::app);
        this->s_verbose.rdbuf(fileOutVerbose.rdbuf());
    }
}
