#include "While.h"

using namespace bash;

While::While (Token* t) : Instruction(t) {}

While::~While() {
    if(cond)
        delete cond;

    for (auto& i : block)
        delete i;
}

void While::visit(Context& ctx) {
    
}

std::string While::to_string() {
    std::string s = "while " + cond->to_string() + " then ";
    for (auto& i : block)
        s += i->to_string() + "; ";
    return s;
}