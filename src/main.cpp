#include <iostream>
#include <string>

#include "bash/interpreter.h"

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::setMinimumDateHoursSize(0);
    Logger::setDatePrinting(false);
    Logger::setHourPrinting(false);
    Logger::redirectToFile(Error | Warning | Log | Info | Verbose, "debugguer.txt");

    Logger::info("===== New Run =====");

    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }

    bash::Interpreter bash_interpreter;

    if (runTest) {
        bash_interpreter.runTest();

        return 0;
    }

    bash_interpreter.interactive();

    return 0;
}