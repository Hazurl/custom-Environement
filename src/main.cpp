#include <iostream>
#include <string>

#include "bash/interpreter.h"

int main (int argc, char* argv[]) {

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