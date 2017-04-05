#include <iostream>
#include <string>

#include "bash/interpreter.h"
#include "bash/LexicalAnalyzer.h"
#include "bash/Token.h"
#include "../lib/Logger/src/Logger.h"

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::createTransport(new Transport("Debug/debugguerColored.txt"), "debugC");
    Logger::setTransportOf(Logger::ALL, "debugC");
    Logger::createTransport(new Transport("Debug/debugguer.txt"), "debug");
    Logger::addTransportOf(Logger::ALL, "debug");
    Logger::allowColorOn("debug", false);

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