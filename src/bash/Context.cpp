#include "Context.h"

using namespace bash;

Context::Context() {}
Context::~Context() {}

Value Context::setVar(std::string name, Value v) {
    if (variables.find(name) == variables.end())
        variables.insert( { name, v });
    else 
        variables[name] = v;
    return v;
}

Value Context::getVar(std::string name) {
    if (variables.find(name) == variables.end())
        variables.insert({ name, Value() });

    return variables[name];
}

std::string Context::to_string () {
    std::string s = "";

    for (auto pair : variables)
        s += pair.first + " : " + pair.second.to_string() + ", ";

    return s;
}

void Context::print(Value const& v) {
    std::cout << v.to_string() << std::endl;
    Logger::spe("Print : " + v.to_string());
}