#include "Context.h"

using namespace bash;

Context::Context(std::map<std::string, void (*) (Context&)>* funcs, std::string progName, std::vector<Value> params) : funcs(funcs) {
    this->params.push_back(Value(progName));
    for (auto& v : params)
        this->params.push_back(v);
}
Context::~Context() {}

Value Context::getParam(unsigned long i) {
    if (i >= params.size())
        return Value();
    return params[i];
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
    std::cout << v.to_string() << std::endl;
    Logger::spe("Print : " + v.to_string());
}

void Context::call(std::string name, std::vector<Value> args) {
    if (!funcs || funcs->find(name) == funcs->end())
        throw std::runtime_error("Cannot call : " + name);

    Context ctx(funcs, name, args);
    (*funcs)[name](ctx);
}