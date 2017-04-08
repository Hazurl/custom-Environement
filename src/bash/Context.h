
#ifndef __BASH_CONTEXT__
#define __BASH_CONTEXT__

#include <map>
#include <string>
#include <iostream>
#include "../../lib/Logger/src/Logger.h"
#include "Value.h"

namespace bash {

class Context {
public:
    Context();
    ~Context();

    Value setVar(std::string name, Value v);
    Value getVar(std::string name);
    std::string to_string();

    void print(Value const& v);

private:
    std::map<std::string, Value> variables;
};

}; // namespace bash

#endif