
#ifndef __BASH_CONTEXT__
#define __BASH_CONTEXT__

#include <map>
#include <string>

namespace bash {

class Context {
public:
    Context();
    ~Context();

    double setVar(std::string name, double value);
    double getVar(std::string name);
    std::string to_string();

private:
    std::map<std::string, double> variables;
};

}; // namespace bash

#endif