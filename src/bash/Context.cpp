#include "Context.h"

using namespace bash;
using namespace haz;

Context::Context(std::map<std::string, void (*) (Context&)>* funcs, std::string progName, std::vector<Value> params) : funcs(funcs), printer(&Context::defaultPrint) {
    logger->setLevel(Level::CONFIG);

    setVar("$0", Value(progName));

    unsigned long i = 1;
    for (auto& v : params)
        setVar("$" + std::to_string(i++), v);
}

Context::~Context() {}

Value Context::getParam(unsigned long i) {
    return getVar("$" + std::to_string(i));
}

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
    printer(v.to_string());
}

void Context::call(std::string name, std::vector<Value> args) {
    if (!funcs || funcs->find(name) == funcs->end())
        logger->THROWEXCEPTION(std::runtime_error, "Cannot call : " + name);

    Context ctx(funcs, name, args);
    ctx.setPrinter(printer);
    (*funcs)[name](ctx);
}

void Context::setPrinter (printer_t new_printer) {
    logger->CONFIG("Change printer");
    this->printer = new_printer;
}

void Context::defaultPrint(std::string str) {
    std::cout << str << std::endl;
}