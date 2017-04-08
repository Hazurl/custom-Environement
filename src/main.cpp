#include <iostream>
#include <string>

#include "bash/Interpreter.h"
#include "bash/Value.h"
#include "../lib/Logger/src/Logger.h"

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::createTransport(new Transport("Debug/debugguerColored.txt"), "debugC");
    Logger::setTransportOf(Logger::ALL, "debugC");

    // Sections
    //Logger::hideSection("Tokenize");
    //Logger::hideSection("Parser");
    //Logger::hideSection("Evaluate");

    Logger::title("Nouveau Run", Logger::SPE);

    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }

    bash::Interpreter bash_interpreter;

    if (runTest) {
        Logger::hideSection("Tokenize");
        Logger::hideSection("Parser");
        Logger::hideSection("Evaluate");
        bash_interpreter.runTest();

        return 0;
    }

    bash_interpreter.interactive();

    return 0;
}