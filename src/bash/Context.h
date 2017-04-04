#include "Context.h"

using namespace bash;

Context::Context() {}
Context::~Context() {}

double Context::setVar(std::string name, double value) {
    if (variables.find(name) == variables.end())
        variables.insert(name, value);
    else 
        variables[name] = value;
    return value;
}

double Context::getVar(std::string name) {
    if (variables.find(name) == variables.end())
        variables.insert(name, 0);

    return variables[name];
}
