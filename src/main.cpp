#include <iostream>
#include <string>

#include <logger.h>
#include "system/System.h"

using namespace haz;
using namespace bash;

int main (int , char**) {
    // Logger : 
    auto fh = new FileHandler("Debug/debugguerColored.txt");
    Logger::get("#").addHandler(fh);
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
    // http://patorjk.com/software/taag/#p=display&h=0&v=0&f=Small&t=START%20APPLICATION
    fh->commonFormat("{endl} ___   _____     _     ___   _____       _     ___   ___   _      ___    ___     _     _____   ___    ___    _  _ {endl}"
                           R"(/ __| |_   _|   /_\\   | _ \\ |_   _|     /_\\   | _ \\ | _ \\ | |    |_ _|  / __|   /_\\   |_   _| |_ _|  / _ \\  | \\| |{endl})"
                           R"(\\__ \\   | |    / _ \\  |   /   | |      / _ \\  |  _/ |  _/ | |__   | |  | (__   / _ \\    | |    | |  | (_) | | .` |{endl})"
                           R"(|___/   |_|   /_/ \\_\\ |_|_\\   |_|     /_/ \\_\\ |_|   |_|   |____| |___|  \\___| /_/ \\_\\   |_|   |___|  \\___/  |_|\\_|{endl}{endl})");
    logger->CONFIG("START");
    fh->commonFormat("[ {hour}:{min}:{sec} ] {col}{func} ({line}){clr} : {bld}{msg}{clr}");
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