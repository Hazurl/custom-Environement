#include <iostream>
#include <string>

#include <logger.h>
#include "system/System.h"

using namespace haz;
using namespace bash;

int main (int argc, char* argv[]) {
    // Logger : 
    Logger::get("#").addHandler(new FileHandler("Debug/debugguerColored.txt"));
                    ;//.addHandler((new FileHandler("Debug/debugguerNoColored.txt"))->color(false));

    Logger* logger = &Logger::get("#.main");
    logger->setColorsLevel({
        { Formatting::RED, 600 },
        { Formatting::YELLOW, 500 },
        { Formatting::MAGENTA, 400 },
        { Formatting::GREEN, 300 },
        { Formatting::BLUE, 200 },
        { Formatting::CYAN, 100 }
    });
    logger->CONFIG("START");

/*
    bool runTest = false;

    for (int i = 1; i < argc; ++i) {
        auto v = std::string(argv[i]);

        if (v == "-t" || v == "-T" || v == "--test") runTest = true;
    }
*/
    System sstm;

    return 0;
}