#include "interpreter.h"

#include <iostream>
#include <string>

using namespace bash;

//      =====   INTERPRETER    =====

Interpreter::Interpreter () {

}

Interpreter::~Interpreter () {

}

void Interpreter::interactive () {
    std::cout << INTERACTIVE_PREFIXE;

    std::cout << std::endl;
}

void Interpreter::runTest () {
    std::cout << "TEST" << std::endl;
}