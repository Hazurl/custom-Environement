
#ifndef __BASH_CONTEXT__
#define __BASH_CONTEXT__

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "../../lib/Logger/src/Logger.h"
#include "Value.h"

namespace bash {

class Context {
public:
    Context(std::map<std::string, void (*) (Context&)>* funcs, std::string progName, std::vector<Value> params);
    ~Context();

    Value getParam(unsigned long i);

    Value setVar(std::string name, Value v);
    Value getVar(std::string name);
    std::string to_string();

    void print(Value const& v);
    void call(std::string name, std::vector<Value> args);

private:
    std::map<std::string, Value> variables;
    std::vector<Value> params;

    std::map<std::string, void (*) (Context&)>* funcs = nullptr;
};

}; // namespace bash

#endif