
#ifndef __BASH_CONTEXT__
#define __BASH_CONTEXT__

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include <logger.h>
#include <functional>
#include "Value.h"

using namespace haz;

namespace bash {

class Context {
public:
    typedef std::function<void(std::string)> printer_t;

    Context(std::map<std::string, void (*) (Context&)>* funcs, std::string progName, std::vector<Value> params);
    ~Context();

    void setPrinter (printer_t printer);

    Value getParam(unsigned long i);

    Value setVar(std::string name, Value v);
    Value getVar(std::string name);
    std::string to_string();

    void print(Value const& v);
    void call(std::string name, std::vector<Value> args);

private:
    Logger* logger = &Logger::get("#.Context");
    std::map<std::string, Value> variables;
    std::vector<Value> params;

    std::map<std::string, void (*) (Context&)>* funcs = nullptr;

    printer_t printer;
    static void defaultPrint (std::string str);
};

}; // namespace bash

#endif