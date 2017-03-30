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
    //Logger::hideSection("Tokens");
    //Logger::hideSection("Parser");
    //Logger::hideSection("Evaluate");

    Logger::log("===== New Run =====");

    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }
/*
    bash::Interpreter bash_interpreter;

    if (runTest) {
        bash_interpreter.runTest();

        return 0;
    }

    bash_interpreter.interactive();
*/

    auto l = bash::LexicalAnalyzer("5 12\t\n   1.0 \t0 5.2 .5 000.500 1. 000000000 999999999999999999.99999 1.2.3 .4 .5. 6 .. \t");

    bash::Token* t;
    while((t = l.eat())->type != bash::Token::Type::END)
        Logger::verbose(
            "At line " + std::to_string(t->linePos) + "(" + std::to_string(t->charPos) + ") \"" + t->content + "\" : " + bash::Token::type_to_string(t->type)
        );

    return 0;
}