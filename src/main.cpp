#include <iostream>
#include <string>

#include "system/System.h"
#include "../lib/Logger/src/Logger.h"

using namespace haz;
using namespace bash;

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::createTransport(new Transport("Debug/debugguerColored.txt"), "debugC");
    Logger::setTransportOf(Logger::ALL, "debugC");

    // Sections
    //Logger::hideSection("Tokenize");
    //Logger::hideSection("Parser");
    //Logger::hideSection("Evaluate");

    Logger::title("Nouveau Run", Logger::SPE);
/*
    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }
*/
    System sstm;
    sstm.getCmd().interactive();

    return 0;
}