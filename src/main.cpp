#include <iostream>
#include <string>

#include "bash/interpreter.h"
#include "bash/LexicalAnalyzer.h"
#include "bash/Token.h"
#include "../lib/Logger/src/Logger.h"

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::setMinimumDateHoursSize(0);
    Logger::setDatePrinting(false);
    Logger::setHourPrinting(false);
    Logger::redirectToFile(Logger::Error | Logger::Warning | Logger::Log | Logger::Info | Logger::Verbose, "Debug/debugguer.txt");

    // Sections
    //Logger::hideSection("Tokenize");
    //Logger::hideSection("Parser");
    //Logger::hideSection("Evaluate");

    Logger::log("===== New Run =====");

    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }

    bash::Interpreter bash_interpreter;

    if (runTest) {
        bash_interpreter.runTest();
        bash_interpreter.run("1 + 2 - (2/2 - 1.2) * . + .6 * 5. + 1 - 1.000");

        return 0;
    }

    bash_interpreter.interactive();


    return 0;
}